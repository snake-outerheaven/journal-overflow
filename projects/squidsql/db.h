/**
 * @file db.h
 * @brief In-memory tables and statement execution.
 */
#ifndef DB_H
#define DB_H

#include <stdio.h>

#include "squid.h"

/** A table: its schema and its rows. */
typedef struct
{
    char name[SQ_NAME_MAX];              /**< Table name (lowercase). */
    int ncols;                           /**< Number of columns. */
    char cols[SQ_MAX_COLS][SQ_NAME_MAX]; /**< Column names. */
    coltype types[SQ_MAX_COLS];          /**< Column types. */
    value *rows; /**< Cells in row-major order: `rows[row * ncols + col]`. */
    int nrows;   /**< Rows in use. */
    int cap;     /**< Rows allocated in #rows. */
} table;

/** A database: a fixed-size catalog of tables. */
typedef struct
{
    table tables[SQ_MAX_TABLES]; /**< Table slots; the first #ntables are used. */
    int ntables;                 /**< Number of existing tables. */
} db;

/**
 * @brief Makes @p d an empty database.
 * @param d Database to initialize.
 */
void db_init(db *d);

/**
 * @brief Releases every table's row storage.
 *
 * The database is left empty and may be reused.
 *
 * @param d Database to clear.
 */
void db_free(db *d);

/**
 * @brief Executes a parsed statement.
 *
 * Results and confirmations (for example `1 row inserted`) are written to
 * @p out. The checks that need the catalog happen here: the table and columns
 * must exist, literal types must match the column types and an INSERT must
 * supply one value per column.
 *
 * @param d   Database to run against.
 * @param st  Statement produced by parse().
 * @param out Stream that receives the output.
 * @param err Buffer of at least ::SQ_ERR_MAX bytes; receives the message on
 *            failure.
 * @return 0 on success, non-zero on failure (the database is unchanged).
 */
int db_exec(db *d, const stmt *st, FILE *out, char *err);

/**
 * @brief Prints the name of every table, one per line.
 * @param d   Database to list.
 * @param out Stream that receives the names.
 */
void db_list_tables(const db *d, FILE *out);

#endif
