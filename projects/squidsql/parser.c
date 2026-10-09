/**
 * @file parser.c
 * @brief Recursive-descent parser for the squidsql SQL subset.
 *
 * Each grammar rule is one `parse_*` function. They all return 0 on success
 * and -1 on error, with the message already stored in parser::err, so callers
 * can chain them with `||`. The grammar is listed in the developer guide.
 */
#include "parser.h"

#include <stdio.h>
#include <string.h>

#include "lexer.h"

/** Parser state: a lexer plus one token of lookahead. */
typedef struct
{
    lexer lx;   /**< Source of tokens. */
    token cur;  /**< Current (not yet consumed) token. */
    char *err;  /**< Caller's buffer for the error message. */
} parser;

/**
 * @brief Records a "syntax error: expected ..." message.
 * @param p    Parser; its current token is quoted in the message.
 * @param what Description of what was expected.
 * @return Always -1, so callers can `return fail(...)`.
 */
static int fail(parser *p, const char *what)
{
    if (p->cur.type == TK_EOF)
    {
        sprintf(p->err, "syntax error: expected %s, got end of input", what);
    }
    else
    {
        sprintf(p->err, "syntax error: expected %s near '%s'", what, p->cur.text);
    }
    return -1;
}

/**
 * @brief Consumes the current token and reads the next one.
 * @param p Parser to advance.
 * @return 0 on success, -1 if the new token is a lexical error.
 */
static int advance(parser *p)
{
    lex_next(&p->lx, &p->cur);
    if (p->cur.type == TK_ERROR)
    {
        sprintf(p->err, "lexical error: %s", p->cur.text);
        return -1;
    }
    return 0;
}

/**
 * @brief Consumes the current token if it has the given type.
 * @param p    Parser.
 * @param type Required token type.
 * @param what Description used in the error message.
 * @return 0 on success, -1 if the token differs or the next one is invalid.
 */
static int expect(parser *p, tk_type type, const char *what)
{
    if (p->cur.type != type)
    {
        return fail(p, what);
    }
    return advance(p);
}

/**
 * @brief Consumes an identifier and copies it into @p dst.
 * @param p    Parser.
 * @param dst  Buffer of ::SQ_NAME_MAX bytes.
 * @param what Description used in the error message.
 * @return 0 on success, -1 if the token is not an identifier or the name is
 *         longer than ::SQ_NAME_MAX - 1.
 */
static int take_ident(parser *p, char *dst, const char *what)
{
    if (p->cur.type != TK_IDENT)
    {
        return fail(p, what);
    }
    if (strlen(p->cur.text) >= SQ_NAME_MAX)
    {
        sprintf(p->err, "name '%s' is too long (max %d)", p->cur.text, SQ_NAME_MAX - 1);
        return -1;
    }
    strcpy(dst, p->cur.text);
    return advance(p);
}

/**
 * @brief Parses an integer or string literal.
 * @param p Parser.
 * @param v Receives the typed value.
 * @return 0 on success, -1 if the token is not a literal.
 */
static int parse_literal(parser *p, value *v)
{
    if (p->cur.type == TK_INT_LIT)
    {
        v->type = TYPE_INT;
        v->i = p->cur.num;
        v->s[0] = '\0';
    }
    else if (p->cur.type == TK_STR_LIT)
    {
        v->type = TYPE_TEXT;
        v->i = 0;
        strcpy(v->s, p->cur.text);
    }
    else
    {
        return fail(p, "a literal (number or 'string')");
    }
    return advance(p);
}

/**
 * @brief Parses an optional `WHERE col op literal` clause.
 *
 * Does nothing if the current token is not WHERE.
 *
 * @param p  Parser.
 * @param st Statement whose #stmt::where and #stmt::has_where are filled.
 * @return 0 on success (including "no WHERE"), -1 on a syntax error.
 */
static int parse_where(parser *p, stmt *st)
{
    if (p->cur.type != TK_WHERE)
    {
        return 0;
    }
    if (advance(p) || take_ident(p, st->where.col, "a column name"))
    {
        return -1;
    }
    switch (p->cur.type)
    {
    case TK_EQ:
        st->where.op = OP_EQ;
        break;
    case TK_NE:
        st->where.op = OP_NE;
        break;
    case TK_LT:
        st->where.op = OP_LT;
        break;
    case TK_LE:
        st->where.op = OP_LE;
        break;
    case TK_GT:
        st->where.op = OP_GT;
        break;
    case TK_GE:
        st->where.op = OP_GE;
        break;
    default:
        return fail(p, "a comparison operator");
    }
    if (advance(p) || parse_literal(p, &st->where.val))
    {
        return -1;
    }
    st->has_where = 1;
    return 0;
}

/**
 * @brief Parses `CREATE TABLE name (col type, ...)`.
 * @param p  Parser positioned on CREATE.
 * @param st Statement to fill.
 * @return 0 on success, -1 on error (including more than ::SQ_MAX_COLS columns).
 */
static int parse_create(parser *p, stmt *st)
{
    st->kind = STMT_CREATE;
    if (advance(p) || expect(p, TK_TABLE, "TABLE") || take_ident(p, st->table, "a table name") ||
        expect(p, TK_LPAREN, "'('"))
    {
        return -1;
    }
    do
    {
        if (st->ncols > 0 && advance(p))
        {
            return -1; /* consume the comma */
        }
        if (st->ncols >= SQ_MAX_COLS)
        {
            sprintf(p->err, "too many columns (max %d)", SQ_MAX_COLS);
            return -1;
        }
        if (take_ident(p, st->cols[st->ncols], "a column name"))
        {
            return -1;
        }
        if (p->cur.type == TK_KW_INT)
        {
            st->types[st->ncols] = TYPE_INT;
        }
        else if (p->cur.type == TK_KW_TEXT)
        {
            st->types[st->ncols] = TYPE_TEXT;
        }
        else
        {
            return fail(p, "a column type (INT or TEXT)");
        }
        st->ncols++;
        if (advance(p))
        {
            return -1;
        }
    } while (p->cur.type == TK_COMMA);
    return expect(p, TK_RPAREN, "')'");
}

/**
 * @brief Parses `INSERT INTO name VALUES (literal, ...)`.
 * @param p  Parser positioned on INSERT.
 * @param st Statement to fill.
 * @return 0 on success, -1 on error (including more than ::SQ_MAX_COLS values).
 */
static int parse_insert(parser *p, stmt *st)
{
    st->kind = STMT_INSERT;
    if (advance(p) || expect(p, TK_INTO, "INTO") || take_ident(p, st->table, "a table name") ||
        expect(p, TK_VALUES, "VALUES") || expect(p, TK_LPAREN, "'('"))
    {
        return -1;
    }
    do
    {
        if (st->nvals > 0 && advance(p))
        {
            return -1;
        }
        if (st->nvals >= SQ_MAX_COLS)
        {
            sprintf(p->err, "too many values (max %d)", SQ_MAX_COLS);
            return -1;
        }
        if (parse_literal(p, &st->vals[st->nvals]))
        {
            return -1;
        }
        st->nvals++;
    } while (p->cur.type == TK_COMMA);
    return expect(p, TK_RPAREN, "')'");
}

/**
 * @brief Parses `SELECT * | col, ... FROM name [WHERE ...]`.
 *
 * For `*` the statement is left with ncols == 0.
 *
 * @param p  Parser positioned on SELECT.
 * @param st Statement to fill.
 * @return 0 on success, -1 on error.
 */
static int parse_select(parser *p, stmt *st)
{
    st->kind = STMT_SELECT;
    if (advance(p))
    {
        return -1;
    }
    if (p->cur.type == TK_STAR)
    {
        if (advance(p))
        {
            return -1;
        }
    }
    else
    {
        do
        {
            if (st->ncols > 0 && advance(p))
            {
                return -1;
            }
            if (st->ncols >= SQ_MAX_COLS)
            {
                sprintf(p->err, "too many columns (max %d)", SQ_MAX_COLS);
                return -1;
            }
            if (take_ident(p, st->cols[st->ncols], "a column name or '*'"))
            {
                return -1;
            }
            st->ncols++;
        } while (p->cur.type == TK_COMMA);
    }
    if (expect(p, TK_FROM, "FROM") || take_ident(p, st->table, "a table name"))
    {
        return -1;
    }
    return parse_where(p, st);
}

/**
 * @brief Parses `DELETE FROM name [WHERE ...]`.
 * @param p  Parser positioned on DELETE.
 * @param st Statement to fill.
 * @return 0 on success, -1 on error.
 */
static int parse_delete(parser *p, stmt *st)
{
    st->kind = STMT_DELETE;
    if (advance(p) || expect(p, TK_FROM, "FROM") || take_ident(p, st->table, "a table name"))
    {
        return -1;
    }
    return parse_where(p, st);
}

int parse(const char *sql, stmt *out, char *err)
{
    parser p;
    int rc;

    memset(out, 0, sizeof *out);
    err[0] = '\0';
    p.err = err;
    lex_init(&p.lx, sql);
    if (advance(&p))
    {
        return -1;
    }

    switch (p.cur.type)
    {
    case TK_CREATE:
        rc = parse_create(&p, out);
        break;
    case TK_INSERT:
        rc = parse_insert(&p, out);
        break;
    case TK_SELECT:
        rc = parse_select(&p, out);
        break;
    case TK_DELETE:
        rc = parse_delete(&p, out);
        break;
    case TK_EOF:
        sprintf(err, "empty statement");
        return -1;
    default:
        return fail(&p, "CREATE, INSERT, SELECT or DELETE");
    }
    if (rc)
    {
        return -1;
    }

    if (p.cur.type == TK_SEMI && advance(&p))
    {
        return -1;
    }
    if (p.cur.type != TK_EOF)
    {
        return fail(&p, "end of statement");
    }
    return 0;
}
