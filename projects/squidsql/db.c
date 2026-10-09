/**
 * @file db.c
 * @brief Implementation of the in-memory database declared in db.h.
 */
#include "db.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void db_init(db *d)
{
    d->ntables = 0;
}

void db_free(db *d)
{
    int i;

    for (i = 0; i < d->ntables; i++)
    {
        free(d->tables[i].rows);
    }
    d->ntables = 0;
}

void db_list_tables(const db *d, FILE *out)
{
    int i;

    for (i = 0; i < d->ntables; i++)
    {
        fprintf(out, "%s\n", d->tables[i].name);
    }
}

/**
 * @brief Looks a table up by name.
 * @param d    Database to search.
 * @param name Table name (already lowercase).
 * @return The table, or NULL if it does not exist.
 */
static table *find_table(db *d, const char *name)
{
    int i;

    for (i = 0; i < d->ntables; i++)
    {
        if (strcmp(d->tables[i].name, name) == 0)
        {
            return &d->tables[i];
        }
    }
    return NULL;
}

/**
 * @brief Finds a column's position in a table.
 * @param t    Table to search.
 * @param name Column name (already lowercase).
 * @return The zero-based column index, or -1 if there is no such column.
 */
static int col_index(const table *t, const char *name)
{
    int i;

    for (i = 0; i < t->ncols; i++)
    {
        if (strcmp(t->cols[i], name) == 0)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Returns the SQL name of a column type, for error messages.
 * @param t Column type.
 * @return `"INT"` or `"TEXT"`.
 */
static const char *type_name(coltype t)
{
    return t == TYPE_INT ? "INT" : "TEXT";
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
        sprintf(buf, "%ld", v->i);
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
 * @param t   Table the statement targets.
 * @param st  Statement being executed.
 * @param idx Receives the column index, or -1 when there is no WHERE.
 * @param err Receives the message on failure.
 * @return 0 on success, -1 on an unknown column or a type mismatch.
 */
static int bind_where(const table *t, const stmt *st, int *idx, char *err)
{
    *idx = -1;
    if (!st->has_where)
    {
        return 0;
    }
    *idx = col_index(t, st->where.col);
    if (*idx < 0)
    {
        sprintf(err, "no such column: %s", st->where.col);
        return -1;
    }
    if (t->types[*idx] != st->where.val.type)
    {
        sprintf(err, "type mismatch: column %s is %s", st->where.col, type_name(t->types[*idx]));
        return -1;
    }
    return 0;
}

/**
 * @brief Tests one row against the WHERE clause.
 * @param t    Table holding the row.
 * @param row  Row index.
 * @param widx Column index from bind_where(), or -1 for no WHERE.
 * @param st   Statement carrying the predicate.
 * @return Non-zero if the row qualifies; always true when @p widx is -1.
 */
static int row_matches(const table *t, int row, int widx, const stmt *st)
{
    if (widx < 0)
    {
        return 1;
    }
    return compare(&t->rows[row * t->ncols + widx], st->where.op, &st->where.val);
}

/**
 * @brief Executes CREATE TABLE.
 *
 * Fails if the table exists, the catalog is full or two columns share a name.
 *
 * @param d   Database.
 * @param st  CREATE statement.
 * @param out Receives the confirmation.
 * @param err Receives the message on failure.
 * @return 0 on success, -1 on failure.
 */
static int exec_create(db *d, const stmt *st, FILE *out, char *err)
{
    table *t;
    int i, j;

    if (find_table(d, st->table))
    {
        sprintf(err, "table already exists: %s", st->table);
        return -1;
    }
    if (d->ntables >= SQ_MAX_TABLES)
    {
        sprintf(err, "too many tables (max %d)", SQ_MAX_TABLES);
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

    t = &d->tables[d->ntables++];
    memset(t, 0, sizeof *t);
    strcpy(t->name, st->table);
    t->ncols = st->ncols;
    for (i = 0; i < st->ncols; i++)
    {
        strcpy(t->cols[i], st->cols[i]);
        t->types[i] = st->types[i];
    }
    fprintf(out, "table %s created\n", t->name);
    return 0;
}

/**
 * @brief Executes INSERT.
 *
 * Checks the value count and each value's type, then appends the row,
 * doubling the row capacity (starting at 8) when it is full.
 *
 * @param d   Database.
 * @param st  INSERT statement.
 * @param out Receives the confirmation.
 * @param err Receives the message on failure.
 * @return 0 on success, -1 on failure (the table is unchanged).
 */
static int exec_insert(db *d, const stmt *st, FILE *out, char *err)
{
    table *t = find_table(d, st->table);
    int i;

    if (!t)
    {
        sprintf(err, "no such table: %s", st->table);
        return -1;
    }
    if (st->nvals != t->ncols)
    {
        sprintf(err, "table %s has %d columns but %d values were supplied", t->name, t->ncols, st->nvals);
        return -1;
    }
    for (i = 0; i < t->ncols; i++)
    {
        if (st->vals[i].type != t->types[i])
        {
            sprintf(err, "type mismatch: column %s is %s", t->cols[i], type_name(t->types[i]));
            return -1;
        }
    }
    if (t->nrows == t->cap)
    {
        int cap = t->cap ? t->cap * 2 : 8;
        value *rows = (value *)realloc(t->rows, (size_t)cap * (size_t)t->ncols * sizeof(value));

        if (!rows)
        {
            sprintf(err, "out of memory");
            return -1;
        }
        t->rows = rows;
        t->cap = cap;
    }
    for (i = 0; i < t->ncols; i++)
    {
        t->rows[t->nrows * t->ncols + i] = st->vals[i];
    }
    t->nrows++;
    fprintf(out, "1 row inserted\n");
    return 0;
}

/**
 * @brief Executes DELETE.
 *
 * Compacts the row array in place, keeping the rows that do not match the
 * WHERE clause (all rows are removed when there is none).
 *
 * @param d   Database.
 * @param st  DELETE statement.
 * @param out Receives the number of deleted rows.
 * @param err Receives the message on failure.
 * @return 0 on success, -1 on failure.
 */
static int exec_delete(db *d, const stmt *st, FILE *out, char *err)
{
    table *t = find_table(d, st->table);
    int widx, r, kept = 0;

    if (!t)
    {
        sprintf(err, "no such table: %s", st->table);
        return -1;
    }
    if (bind_where(t, st, &widx, err))
    {
        return -1;
    }
    for (r = 0; r < t->nrows; r++)
    {
        if (row_matches(t, r, widx, st))
        {
            continue;
        }
        if (kept != r)
        {
            memcpy(&t->rows[kept * t->ncols], &t->rows[r * t->ncols], (size_t)t->ncols * sizeof(value));
        }
        kept++;
    }
    fprintf(out, "%d row(s) deleted\n", t->nrows - kept);
    t->nrows = kept;
    return 0;
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
 * Two passes over the rows: the first computes column widths and the match
 * count, the second prints.
 *
 * @param d   Database.
 * @param st  SELECT statement.
 * @param out Receives the result.
 * @param err Receives the message on failure.
 * @return 0 on success, -1 on an unknown table or column, or a type mismatch.
 */
static int exec_select(db *d, const stmt *st, FILE *out, char *err)
{
    table *t = find_table(d, st->table);
    int proj[SQ_MAX_COLS];
    int widths[SQ_MAX_COLS];
    int nproj, widx, r, i, matched = 0;
    char buf[SQ_TEXT_MAX + 24];

    if (!t)
    {
        sprintf(err, "no such table: %s", st->table);
        return -1;
    }
    if (st->ncols == 0)
    {
        nproj = t->ncols;
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
            proj[i] = col_index(t, st->cols[i]);
            if (proj[i] < 0)
            {
                sprintf(err, "no such column: %s", st->cols[i]);
                return -1;
            }
        }
    }
    if (bind_where(t, st, &widx, err))
    {
        return -1;
    }

    /* first pass: column widths and match count */
    for (i = 0; i < nproj; i++)
    {
        widths[i] = (int)strlen(t->cols[proj[i]]);
    }
    for (r = 0; r < t->nrows; r++)
    {
        if (!row_matches(t, r, widx, st))
        {
            continue;
        }
        matched++;
        for (i = 0; i < nproj; i++)
        {
            int len;

            value_str(&t->rows[r * t->ncols + proj[i]], buf);
            len = (int)strlen(buf);
            if (len > widths[i])
            {
                widths[i] = len;
            }
        }
    }

    /* second pass: print */
    for (i = 0; i < nproj; i++)
    {
        fprintf(out, "%s%-*s", i ? " | " : " ", widths[i], t->cols[proj[i]]);
    }
    fputc('\n', out);
    print_rule(out, widths, nproj);
    for (r = 0; r < t->nrows; r++)
    {
        if (!row_matches(t, r, widx, st))
        {
            continue;
        }
        for (i = 0; i < nproj; i++)
        {
            value_str(&t->rows[r * t->ncols + proj[i]], buf);
            fprintf(out, "%s%-*s", i ? " | " : " ", widths[i], buf);
        }
        fputc('\n', out);
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
