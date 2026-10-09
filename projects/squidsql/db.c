/**
 * @file db.c
 * @brief Implementation of the disk-backed database declared in db.h.
 *
 * Throughout this file a table, a name or a row is held as an arena
 * **offset**. Pointers obtained with arena_ptr() are used only briefly and
 * are re-derived after any call that can allocate, because allocation may
 * remap the file.
 */
#include "db.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

_Static_assert(SQ_ERR_MAX >= HAL_ERR_MAX, "db error buffers must hold HAL messages");

/** Upper bound on the encoded size of one row (INT: 8 bytes; TEXT: 1 + 63). */
#define ROW_BUF_MAX (SQ_MAX_COLS * SQ_TEXT_MAX)

/** One column definition as stored in a table record. */
typedef struct
{
    char name[SQ_NAME_MAX]; /**< Column name. */
    uint32_t type;          /**< A ::coltype. */
    uint32_t reserved;      /**< Padding, kept zero. */
} col_def;

/** A table record as stored in the arena. This is the on-disk format. */
typedef struct
{
    uint64_t name_off;         /**< Offset of the NUL-terminated table name. */
    uint64_t rows_root;        /**< Root of the row tree (see rbtree.h, "root_ref"). */
    uint64_t next_rowid;       /**< Row id the next INSERT will receive; starts at 1. */
    uint64_t nrows;            /**< Number of rows. */
    uint32_t ncols;            /**< Number of columns. */
    uint32_t reserved;         /**< Padding, kept zero. */
    col_def cols[SQ_MAX_COLS]; /**< Column definitions. */
} table_meta;

/**
 * @brief Compares a catalog node key (offset of a table name) with a name.
 * @param a        Arena.
 * @param node_key Offset of the stored name.
 * @param key      `const char *` name being searched.
 * @return strcmp() of the two names.
 */
static int cat_cmp(const arena *a, uint64_t node_key, const void *key)
{
    return strcmp((const char *)arena_ptr(a, node_key), (const char *)key);
}

/**
 * @brief Compares a row-tree node key with a row id.
 * @param a        Arena (unused).
 * @param node_key The stored row id.
 * @param key      `const uint64_t *` row id being searched.
 * @return Negative, zero or positive as the stored id is less, equal or greater.
 */
static int rowid_cmp(const arena *a, uint64_t node_key, const void *key)
{
    uint64_t k = *(const uint64_t *)key;

    (void)a;
    return (node_key > k) - (node_key < k);
}

int db_open(db *d, const char *path, char *err)
{
    memset(d, 0, sizeof *d);
    if (arena_open(&d->a, path, err))
    {
        return -1;
    }
    rb_init(&d->catalog, &d->a, offsetof(arena_header, catalog_root), cat_cmp);
    d->sync = true;
    return 0;
}

void db_set_sync(db *d, bool on)
{
    d->sync = on;
}

void db_close(db *d)
{
    arena_close(&d->a);
}

bool db_was_unclean(const db *d)
{
    return d->a.unclean;
}

/**
 * @brief Resolves a table record offset to a pointer.
 * @param d   Database.
 * @param off Offset of a table record.
 * @return Pointer valid until the next allocation.
 */
static table_meta *meta(const db *d, uint64_t off)
{
    return (table_meta *)arena_ptr(&d->a, off);
}

/**
 * @brief Looks a table up by name.
 * @param d    Database.
 * @param name Table name (already lowercase).
 * @return Offset of the table record, or 0 if the table does not exist.
 */
static uint64_t find_table(const db *d, const char *name)
{
    uint64_t n = rb_find(&d->catalog, name);

    return n ? rb_val(&d->catalog, n) : 0;
}

/**
 * @brief Builds a handle to a table's row tree.
 * @param d    Database.
 * @param moff Offset of the table record.
 * @param t    Receives the handle.
 */
static void rows_tree(db *d, uint64_t moff, rb_tree *t)
{
    rb_init(t, &d->a, moff + offsetof(table_meta, rows_root), rowid_cmp);
}

void db_list_tables(const db *d, FILE *out)
{
    uint64_t n;

    for (n = rb_first(&d->catalog); n; n = rb_next(&d->catalog, n))
    {
        fprintf(out, "%s\n", (const char *)arena_ptr(&d->a, rb_key(&d->catalog, n)));
    }
}

/**
 * @brief Finds a column's position in a table.
 * @param m    Table record.
 * @param name Column name (already lowercase).
 * @return The zero-based column index, or -1 if there is no such column.
 */
static int col_index(const table_meta *m, const char *name)
{
    uint32_t i;

    for (i = 0; i < m->ncols; i++)
    {
        if (strcmp(m->cols[i].name, name) == 0)
        {
            return (int)i;
        }
    }
    return -1;
}

/**
 * @brief Returns the SQL name of a column type, for error messages.
 * @param t Column type.
 * @return `"INT"` or `"TEXT"`.
 */
static const char *type_name(uint32_t t)
{
    return t == TYPE_INT ? "INT" : "TEXT";
}

/**
 * @brief Packs a row into its on-disk form.
 * @param m   Table record, for the column types.
 * @param v   One value per column.
 * @param buf Output buffer of ::ROW_BUF_MAX bytes.
 * @return Number of bytes written.
 */
static size_t encode_row(const table_meta *m, const value *v, unsigned char *buf)
{
    size_t n = 0;
    uint32_t i;

    for (i = 0; i < m->ncols; i++)
    {
        if (m->cols[i].type == TYPE_INT)
        {
            memcpy(buf + n, &v[i].i, sizeof v[i].i);
            n += sizeof v[i].i;
        }
        else
        {
            size_t len = strlen(v[i].s);

            buf[n++] = (unsigned char)len;
            memcpy(buf + n, v[i].s, len);
            n += len;
        }
    }
    return n;
}

/**
 * @brief Unpacks a row from its on-disk form.
 * @param m   Table record, for the column types.
 * @param p   Start of the row record.
 * @param out Receives one value per column.
 */
static void decode_row(const table_meta *m, const unsigned char *p, value *out)
{
    uint32_t i;

    for (i = 0; i < m->ncols; i++)
    {
        out[i].type = (coltype)m->cols[i].type;
        if (m->cols[i].type == TYPE_INT)
        {
            memcpy(&out[i].i, p, sizeof out[i].i);
            out[i].s[0] = '\0';
            p += sizeof out[i].i;
        }
        else
        {
            size_t len = *p++;

            out[i].i = 0;
            memcpy(out[i].s, p, len);
            out[i].s[len] = '\0';
            p += len;
        }
    }
}

/**
 * @brief Renders a value as text.
 * @param v   Value to render.
 * @param buf Output buffer of at least ::SQ_TEXT_MAX + 24 bytes.
 */
static void value_str(const value *v, char *buf)
{
    if (v->type == TYPE_INT)
    {
        sprintf(buf, "%lld", (long long)v->i);
    }
    else
    {
        strcpy(buf, v->s);
    }
}

/**
 * @brief Evaluates `a op b`.
 *
 * Integers compare numerically, text with strcmp(). Both values must have the
 * same type; bind_where() guarantees that before any row is tested.
 *
 * @param a  Left operand (a table cell).
 * @param op Comparison operator.
 * @param b  Right operand (the WHERE literal).
 * @return Non-zero if the comparison holds.
 */
static int compare(const value *a, cmp_op op, const value *b)
{
    int c;

    if (a->type == TYPE_INT)
    {
        c = (a->i > b->i) - (a->i < b->i);
    }
    else
    {
        c = strcmp(a->s, b->s);
    }
    switch (op)
    {
    case OP_EQ:
        return c == 0;
    case OP_NE:
        return c != 0;
    case OP_LT:
        return c < 0;
    case OP_LE:
        return c <= 0;
    case OP_GT:
        return c > 0;
    case OP_GE:
        return c >= 0;
    }
    return 0;
}

/**
 * @brief Resolves a statement's WHERE clause against a table.
 *
 * Checks that the column exists and that the literal has the column's type,
 * once, before any row is visited.
 *
 * @param m   Table record.
 * @param st  Statement being executed.
 * @param idx Receives the column index, or -1 when there is no WHERE.
 * @param err Receives the message on failure.
 * @return 0 on success, -1 on an unknown column or a type mismatch.
 */
static int bind_where(const table_meta *m, const stmt *st, int *idx, char *err)
{
    *idx = -1;
    if (!st->has_where)
    {
        return 0;
    }
    *idx = col_index(m, st->where.col);
    if (*idx < 0)
    {
        sprintf(err, "no such column: %s", st->where.col);
        return -1;
    }
    if (m->cols[*idx].type != (uint32_t)st->where.val.type)
    {
        sprintf(err, "type mismatch: column %s is %s", st->where.col, type_name(m->cols[*idx].type));
        return -1;
    }
    return 0;
}

/**
 * @brief Tests one decoded row against the WHERE clause.
 * @param row  The row's values.
 * @param widx Column index from bind_where(), or -1 for no WHERE.
 * @param st   Statement carrying the predicate.
 * @return Non-zero if the row qualifies; always true when @p widx is -1.
 */
static int row_matches(const value *row, int widx, const stmt *st)
{
    if (widx < 0)
    {
        return 1;
    }
    return compare(&row[widx], st->where.op, &st->where.val);
}

/**
 * @brief Flushes the file after a change, unless syncing is turned off.
 * @param d   Database.
 * @param err Receives the message on failure.
 * @return 0 on success, -1 on failure.
 */
static int flush(db *d, char *err)
{
    return d->sync ? arena_sync(&d->a, err) : 0;
}

/**
 * @brief Executes CREATE TABLE.
 *
 * Fails if the table exists or two columns share a name.
 *
 * @param d   Database.
 * @param st  CREATE statement.
 * @param out Receives the confirmation.
 * @param err Receives the message on failure.
 * @return 0 on success, -1 on failure.
 */
static int exec_create(db *d, const stmt *st, FILE *out, char *err)
{
    uint64_t name_off, moff;
    table_meta *m;
    rb_status rc;
    int i, j;

    if (find_table(d, st->table))
    {
        sprintf(err, "table already exists: %s", st->table);
        return -1;
    }
    for (i = 0; i < st->ncols; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (strcmp(st->cols[i], st->cols[j]) == 0)
            {
                sprintf(err, "duplicate column: %s", st->cols[i]);
                return -1;
            }
        }
    }

    name_off = arena_alloc(&d->a, strlen(st->table) + 1);
    moff = name_off ? arena_alloc(&d->a, sizeof(table_meta)) : 0;
    if (!moff)
    {
        arena_free(&d->a, name_off);
        sprintf(err, "database is full: cannot grow the file");
        return -1;
    }
    strcpy((char *)arena_ptr(&d->a, name_off), st->table);

    m = meta(d, moff);
    m->name_off = name_off;
    m->next_rowid = 1;
    m->ncols = (uint32_t)st->ncols;
    for (i = 0; i < st->ncols; i++)
    {
        strcpy(m->cols[i].name, st->cols[i]);
        m->cols[i].type = (uint32_t)st->types[i];
    }

    rc = rb_insert(&d->catalog, st->table, name_off, moff);
    if (rc != RB_OK)
    {
        arena_free(&d->a, moff);
        arena_free(&d->a, name_off);
        sprintf(err, "database is full: cannot grow the file");
        return -1;
    }
    fprintf(out, "table %s created\n", st->table);
    return flush(d, err);
}

/**
 * @brief Executes INSERT.
 *
 * Checks the value count and each value's type, writes the row record, then
 * adds it to the table's row tree under the next row id.
 *
 * @param d   Database.
 * @param st  INSERT statement.
 * @param out Receives the confirmation.
 * @param err Receives the message on failure.
 * @return 0 on success, -1 on failure (the table is unchanged).
 */
static int exec_insert(db *d, const stmt *st, FILE *out, char *err)
{
    uint64_t moff = find_table(d, st->table), roff, rowid;
    unsigned char buf[ROW_BUF_MAX];
    table_meta *m;
    rb_tree rows;
    size_t n;
    uint32_t i;

    if (!moff)
    {
        sprintf(err, "no such table: %s", st->table);
        return -1;
    }
    m = meta(d, moff);
    if ((uint32_t)st->nvals != m->ncols)
    {
        sprintf(err, "table %s has %u columns but %d values were supplied", st->table, (unsigned)m->ncols,
                st->nvals);
        return -1;
    }
    for (i = 0; i < m->ncols; i++)
    {
        if ((uint32_t)st->vals[i].type != m->cols[i].type)
        {
            sprintf(err, "type mismatch: column %s is %s", m->cols[i].name, type_name(m->cols[i].type));
            return -1;
        }
    }

    n = encode_row(m, st->vals, buf);
    roff = arena_alloc(&d->a, n);
    if (!roff)
    {
        sprintf(err, "database is full: cannot grow the file");
        return -1;
    }
    memcpy(arena_ptr(&d->a, roff), buf, n);

    rowid = meta(d, moff)->next_rowid; /* re-derive: the file may have moved */
    rows_tree(d, moff, &rows);
    if (rb_insert(&rows, &rowid, rowid, roff) != RB_OK)
    {
        arena_free(&d->a, roff);
        sprintf(err, "database is full: cannot grow the file");
        return -1;
    }
    m = meta(d, moff);
    m->next_rowid++;
    m->nrows++;

    fprintf(out, "1 row inserted\n");
    return flush(d, err);
}

/**
 * @brief Executes DELETE.
 *
 * Walks the row tree in order. The successor is read before a row is removed;
 * deletion never moves surviving nodes, so that offset stays valid.
 *
 * @param d   Database.
 * @param st  DELETE statement.
 * @param out Receives the number of deleted rows.
 * @param err Receives the message on failure.
 * @return 0 on success, -1 on failure.
 */
static int exec_delete(db *d, const stmt *st, FILE *out, char *err)
{
    uint64_t moff = find_table(d, st->table), n, next;
    value row[SQ_MAX_COLS];
    rb_tree rows;
    int widx, deleted = 0;

    if (!moff)
    {
        sprintf(err, "no such table: %s", st->table);
        return -1;
    }
    if (bind_where(meta(d, moff), st, &widx, err))
    {
        return -1;
    }

    rows_tree(d, moff, &rows);
    for (n = rb_first(&rows); n; n = next)
    {
        uint64_t roff = rb_val(&rows, n);

        next = rb_next(&rows, n);
        decode_row(meta(d, moff), (const unsigned char *)arena_ptr(&d->a, roff), row);
        if (!row_matches(row, widx, st))
        {
            continue;
        }
        rb_delete(&rows, n);
        arena_free(&d->a, roff);
        meta(d, moff)->nrows--;
        deleted++;
    }
    fprintf(out, "%d row(s) deleted\n", deleted);
    return flush(d, err);
}

/**
 * @brief Prints the dashed line between a result's header and its rows.
 * @param out    Output stream.
 * @param widths Display width of each column.
 * @param n      Number of columns.
 */
static void print_rule(FILE *out, const int *widths, int n)
{
    int i, k;

    for (i = 0; i < n; i++)
    {
        if (i > 0)
        {
            fputc('+', out);
        }
        for (k = 0; k < widths[i] + 2; k++)
        {
            fputc('-', out);
        }
    }
    fputc('\n', out);
}

/**
 * @brief Executes SELECT and prints the result as an aligned table.
 *
 * Two passes over the row tree: the first computes column widths and the
 * match count, the second prints. Rows come out in insertion order.
 *
 * @param d   Database.
 * @param st  SELECT statement.
 * @param out Receives the result.
 * @param err Receives the message on failure.
 * @return 0 on success, -1 on an unknown table or column, or a type mismatch.
 */
static int exec_select(db *d, const stmt *st, FILE *out, char *err)
{
    uint64_t moff = find_table(d, st->table), n;
    const table_meta *m;
    int proj[SQ_MAX_COLS], widths[SQ_MAX_COLS];
    int nproj, widx, i, matched = 0, pass;
    value row[SQ_MAX_COLS];
    char buf[SQ_TEXT_MAX + 24];
    rb_tree rows;

    if (!moff)
    {
        sprintf(err, "no such table: %s", st->table);
        return -1;
    }
    m = meta(d, moff); /* nothing below allocates, so this pointer stays valid */
    if (st->ncols == 0)
    {
        nproj = (int)m->ncols;
        for (i = 0; i < nproj; i++)
        {
            proj[i] = i;
        }
    }
    else
    {
        nproj = st->ncols;
        for (i = 0; i < nproj; i++)
        {
            proj[i] = col_index(m, st->cols[i]);
            if (proj[i] < 0)
            {
                sprintf(err, "no such column: %s", st->cols[i]);
                return -1;
            }
        }
    }
    if (bind_where(m, st, &widx, err))
    {
        return -1;
    }

    for (i = 0; i < nproj; i++)
    {
        widths[i] = (int)strlen(m->cols[proj[i]].name);
    }
    rows_tree(d, moff, &rows);

    for (pass = 0; pass < 2; pass++)
    {
        if (pass == 1)
        {
            for (i = 0; i < nproj; i++)
            {
                fprintf(out, "%s%-*s", i ? " | " : " ", widths[i], m->cols[proj[i]].name);
            }
            fputc('\n', out);
            print_rule(out, widths, nproj);
        }
        for (n = rb_first(&rows); n; n = rb_next(&rows, n))
        {
            decode_row(m, (const unsigned char *)arena_ptr(&d->a, rb_val(&rows, n)), row);
            if (!row_matches(row, widx, st))
            {
                continue;
            }
            for (i = 0; i < nproj; i++)
            {
                value_str(&row[proj[i]], buf);
                if (pass == 0)
                {
                    int len = (int)strlen(buf);

                    if (len > widths[i])
                    {
                        widths[i] = len;
                    }
                }
                else
                {
                    fprintf(out, "%s%-*s", i ? " | " : " ", widths[i], buf);
                }
            }
            if (pass == 0)
            {
                matched++;
            }
            else
            {
                fputc('\n', out);
            }
        }
    }
    fprintf(out, "(%d row%s)\n", matched, matched == 1 ? "" : "s");
    return 0;
}

int db_exec(db *d, const stmt *st, FILE *out, char *err)
{
    err[0] = '\0';
    switch (st->kind)
    {
    case STMT_CREATE:
        return exec_create(d, st, out, err);
    case STMT_INSERT:
        return exec_insert(d, st, out, err);
    case STMT_SELECT:
        return exec_select(d, st, out, err);
    case STMT_DELETE:
        return exec_delete(d, st, out, err);
    }
    sprintf(err, "unsupported statement");
    return -1;
}
