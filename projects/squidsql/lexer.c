/**
 * @file lexer.c
 * @brief Implementation of the SQL lexer declared in lexer.h.
 */
#include "lexer.h"

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/** Reserved words, spelled in uppercase, and the token each one produces. */
static const struct
{
    const char *name;
    tk_type type;
} keywords[] = {{"CREATE", TK_CREATE}, {"TABLE", TK_TABLE}, {"INSERT", TK_INSERT}, {"INTO", TK_INTO},
                {"VALUES", TK_VALUES}, {"SELECT", TK_SELECT}, {"FROM", TK_FROM},   {"WHERE", TK_WHERE},
                {"DELETE", TK_DELETE}, {"INT", TK_KW_INT},    {"TEXT", TK_KW_TEXT}};

/**
 * @brief Turns @p t into a ::TK_ERROR token carrying @p msg.
 * @param t   Token to overwrite.
 * @param msg Message; truncated to fit token::text.
 */
static void set_error(token *t, const char *msg)
{
    t->type = TK_ERROR;
    strncpy(t->text, msg, SQ_TEXT_MAX - 1);
    t->text[SQ_TEXT_MAX - 1] = '\0';
}

/**
 * @brief Classifies a word as a keyword or an identifier.
 * @param upper The word, already converted to uppercase.
 * @return The keyword's token type, or ::TK_IDENT if it is not reserved.
 */
static tk_type keyword_type(const char *upper)
{
    size_t i;

    for (i = 0; i < sizeof keywords / sizeof keywords[0]; i++)
    {
        if (strcmp(keywords[i].name, upper) == 0)
        {
            return keywords[i].type;
        }
    }
    return TK_IDENT;
}

void lex_init(lexer *lx, const char *src)
{
    lx->src = src;
    lx->pos = 0;
}

/**
 * @brief Reads a keyword or identifier starting at the cursor.
 *
 * Words are `[A-Za-z0-9_]+`. The token text is lowercased, which is what makes
 * names case-insensitive.
 *
 * @param lx Lexer positioned on the first letter or underscore.
 * @param t  Receives the token, or a ::TK_ERROR if the word is too long.
 */
static void lex_word(lexer *lx, token *t)
{
    const char *s = lx->src;
    char upper[SQ_TEXT_MAX];
    size_t n = 0;

    while (isalnum((unsigned char)s[lx->pos]) || s[lx->pos] == '_')
    {
        if (n >= SQ_TEXT_MAX - 1)
        {
            set_error(t, "identifier too long");
            return;
        }
        t->text[n] = (char)tolower((unsigned char)s[lx->pos]);
        upper[n] = (char)toupper((unsigned char)s[lx->pos]);
        n++;
        lx->pos++;
    }
    t->text[n] = '\0';
    upper[n] = '\0';
    t->type = keyword_type(upper);
}

/**
 * @brief Reads an integer literal with an optional leading `-`.
 * @param lx Lexer positioned on a digit, or on a `-` followed by a digit.
 * @param t  Receives a ::TK_INT_LIT, or a ::TK_ERROR if the value overflows
 *           a `long` or has too many digits.
 */
static void lex_number(lexer *lx, token *t)
{
    const char *s = lx->src;
    size_t n = 0;
    char *end;

    if (s[lx->pos] == '-')
    {
        t->text[n++] = '-';
        lx->pos++;
    }
    while (isdigit((unsigned char)s[lx->pos]))
    {
        if (n >= SQ_TEXT_MAX - 1)
        {
            set_error(t, "number too long");
            return;
        }
        t->text[n++] = s[lx->pos++];
    }
    t->text[n] = '\0';

    errno = 0;
    t->num = strtol(t->text, &end, 10);
    if (errno == ERANGE)
    {
        set_error(t, "number out of range");
        return;
    }
    t->type = TK_INT_LIT;
}

/**
 * @brief Reads a single-quoted string literal.
 *
 * Two consecutive quotes inside the string stand for one quote character.
 *
 * @param lx Lexer positioned on the opening quote.
 * @param t  Receives a ::TK_STR_LIT with the unquoted text, or a ::TK_ERROR
 *           if the string is unterminated or too long.
 */
static void lex_string(lexer *lx, token *t)
{
    const char *s = lx->src;
    size_t n = 0;

    lx->pos++; /* opening quote */
    for (;;)
    {
        if (s[lx->pos] == '\0')
        {
            set_error(t, "unterminated string");
            return;
        }
        if (s[lx->pos] == '\'')
        {
            if (s[lx->pos + 1] != '\'')
            {
                break;
            }
            lx->pos++; /* '' is an escaped quote */
        }
        if (n >= SQ_TEXT_MAX - 1)
        {
            set_error(t, "string too long");
            return;
        }
        t->text[n++] = s[lx->pos++];
    }
    lx->pos++; /* closing quote */
    t->text[n] = '\0';
    t->type = TK_STR_LIT;
}

void lex_next(lexer *lx, token *t)
{
    const char *s = lx->src;
    char c;

    while (isspace((unsigned char)s[lx->pos]))
    {
        lx->pos++;
    }
    t->text[0] = '\0';
    t->num = 0;
    c = s[lx->pos];

    if (c == '\0')
    {
        t->type = TK_EOF;
        return;
    }
    if (isalpha((unsigned char)c) || c == '_')
    {
        lex_word(lx, t);
        return;
    }
    if (isdigit((unsigned char)c) || (c == '-' && isdigit((unsigned char)s[lx->pos + 1])))
    {
        lex_number(lx, t);
        return;
    }
    if (c == '\'')
    {
        lex_string(lx, t);
        return;
    }

    lx->pos++;
    t->text[0] = c;
    t->text[1] = '\0';
    switch (c)
    {
    case ',':
        t->type = TK_COMMA;
        break;
    case '(':
        t->type = TK_LPAREN;
        break;
    case ')':
        t->type = TK_RPAREN;
        break;
    case '*':
        t->type = TK_STAR;
        break;
    case ';':
        t->type = TK_SEMI;
        break;
    case '=':
        t->type = TK_EQ;
        break;
    case '<':
        if (s[lx->pos] == '=')
        {
            lx->pos++;
            t->type = TK_LE;
        }
        else if (s[lx->pos] == '>')
        {
            lx->pos++;
            t->type = TK_NE;
        }
        else
        {
            t->type = TK_LT;
        }
        break;
    case '>':
        if (s[lx->pos] == '=')
        {
            lx->pos++;
            t->type = TK_GE;
        }
        else
        {
            t->type = TK_GT;
        }
        break;
    case '!':
        if (s[lx->pos] == '=')
        {
            lx->pos++;
            t->type = TK_NE;
        }
        else
        {
            set_error(t, "unexpected character");
        }
        break;
    default:
        set_error(t, "unexpected character");
        break;
    }
}
