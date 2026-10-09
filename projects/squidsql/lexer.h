/**
 * @file lexer.h
 * @brief Lexical analysis: turns SQL text into tokens.
 */
#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

#include "squid.h"

/** Token categories. */
typedef enum
{
    TK_EOF,     /**< End of input. */
    TK_ERROR,   /**< Lexical error; token::text holds the message. */
    TK_IDENT,   /**< Identifier (table or column name). */
    TK_INT_LIT, /**< Integer literal; the value is in token::num. */
    TK_STR_LIT, /**< String literal; the unquoted text is in token::text. */
    TK_COMMA,   /**< `,` */
    TK_LPAREN,  /**< `(` */
    TK_RPAREN,  /**< `)` */
    TK_STAR,    /**< `*` */
    TK_SEMI,    /**< `;` */
    TK_EQ,      /**< `=` */
    TK_NE,      /**< `!=` or `<>` */
    TK_LT,      /**< `<` */
    TK_LE,      /**< `<=` */
    TK_GT,      /**< `>` */
    TK_GE,      /**< `>=` */
    TK_CREATE,  /**< Keyword CREATE. */
    TK_TABLE,   /**< Keyword TABLE. */
    TK_INSERT,  /**< Keyword INSERT. */
    TK_INTO,    /**< Keyword INTO. */
    TK_VALUES,  /**< Keyword VALUES. */
    TK_SELECT,  /**< Keyword SELECT. */
    TK_FROM,    /**< Keyword FROM. */
    TK_WHERE,   /**< Keyword WHERE. */
    TK_DELETE,  /**< Keyword DELETE. */
    TK_KW_INT,  /**< Type keyword INT. */
    TK_KW_TEXT  /**< Type keyword TEXT. */
} tk_type;

/** One lexical token. */
typedef struct
{
    tk_type type;           /**< Category of the token. */
    char text[SQ_TEXT_MAX]; /**< Spelling; identifiers are lowercased. */
    long num;               /**< Numeric value of a ::TK_INT_LIT. */
} token;

/** Cursor over the SQL text being tokenized. */
typedef struct
{
    const char *src; /**< The text; not copied, must outlive the lexer. */
    size_t pos;      /**< Offset of the next unread character. */
} lexer;

/**
 * @brief Starts tokenizing @p src from its first character.
 * @param lx  Lexer to initialize.
 * @param src NUL-terminated SQL text. It is not copied.
 */
void lex_init(lexer *lx, const char *src);

/**
 * @brief Reads the next token.
 *
 * Keywords are case-insensitive. Lexical errors (unterminated string,
 * unexpected character, number out of range, over-long word) are reported as
 * a token of type ::TK_ERROR whose text is the message. At the end of input
 * ::TK_EOF is returned, repeatedly.
 *
 * @param lx Lexer to advance.
 * @param t  Receives the token.
 */
void lex_next(lexer *lx, token *t);

#endif
