/**
 * @file squid.h
 * @brief Types and limits shared by every squidsql module.
 *
 * The lexer, parser and database only know each other through the types
 * declared here: the parser produces a ::stmt and the database consumes it.
 */
#ifndef SQUID_H
#define SQUID_H

#include <stdint.h>

/** @name Fixed limits
 * Names, text values and columns are fixed-size; the number of tables and
 * rows is limited only by disk space.
 * @{ */
#define SQ_NAME_MAX 32 /**< Bytes for a table/column name, with the NUL. */
#define SQ_TEXT_MAX 64 /**< Bytes for a TEXT value or token, with the NUL. */
#define SQ_MAX_COLS 8  /**< Maximum columns per table, and values per row. */
#define SQ_ERR_MAX 160 /**< Size of the buffer that receives error messages. */
/** @} */

/** Column data types. */
typedef enum
{
    TYPE_INT, /**< 64-bit signed integer. */
    TYPE_TEXT /**< Character string of at most ::SQ_TEXT_MAX - 1 bytes. */
} coltype;

/** A typed value: a literal in a statement or a cell in a table. */
typedef struct
{
    coltype type;       /**< Selects which member below is meaningful. */
    int64_t i;          /**< The value when #type is ::TYPE_INT. */
    char s[SQ_TEXT_MAX]; /**< The value when #type is ::TYPE_TEXT. */
} value;

/** Comparison operators allowed in a WHERE clause. */
typedef enum
{
    OP_EQ, /**< `=`        */
    OP_NE, /**< `!=`, `<>` */
    OP_LT, /**< `<`        */
    OP_LE, /**< `<=`       */
    OP_GT, /**< `>`        */
    OP_GE  /**< `>=`       */
} cmp_op;

/** Kinds of statement squidsql understands. */
typedef enum
{
    STMT_CREATE, /**< `CREATE TABLE` */
    STMT_INSERT, /**< `INSERT INTO`   */
    STMT_SELECT, /**< `SELECT`        */
    STMT_DELETE  /**< `DELETE FROM`   */
} stmt_kind;

/** A single WHERE condition: `col op val`. */
typedef struct
{
    char col[SQ_NAME_MAX]; /**< Column name (lowercase). */
    cmp_op op;             /**< Comparison operator. */
    value val;             /**< Literal to compare against. */
} predicate;

/**
 * A parsed statement.
 *
 * One flat struct serves all statement kinds; which fields are meaningful
 * depends on #kind:
 *
 * | kind        | fields used                                              |
 * | ----------- | -------------------------------------------------------- |
 * | ::STMT_CREATE | #table, #ncols, #cols, #types                          |
 * | ::STMT_INSERT | #table, #nvals, #vals                                  |
 * | ::STMT_SELECT | #table, #ncols/#cols (0 columns means `*`), WHERE      |
 * | ::STMT_DELETE | #table, WHERE                                          |
 *
 * "WHERE" means #has_where and #where.
 */
typedef struct
{
    stmt_kind kind;                       /**< Which statement this is. */
    char table[SQ_NAME_MAX];              /**< Target table name. */
    int ncols;                            /**< Number of entries in #cols. */
    char cols[SQ_MAX_COLS][SQ_NAME_MAX];  /**< Column names (CREATE) or projection (SELECT). */
    coltype types[SQ_MAX_COLS];           /**< Column types (CREATE only). */
    int nvals;                            /**< Number of entries in #vals. */
    value vals[SQ_MAX_COLS];              /**< Row to insert (INSERT only). */
    int has_where;                        /**< Non-zero when #where is set. */
    predicate where;                      /**< The WHERE condition, if any. */
} stmt;

#endif
