/**
 * @file db.h
 * @brief The database: tables stored in a memory-mapped file.
 *
 * ### On-disk model
 *
 * All data lives in one file managed by the arena (arena.h) and is linked by
 * offsets:
 *
 * - The **catalog** is a red-black tree keyed by table name. Its root is
 *   arena_header::catalog_root. Each node's value is the offset of a table
 *   record.
 * - A **table record** holds the schema, a row counter and the root of the
 *   table's **row tree**.
 * - The row tree is a red-black tree keyed by a 64-bit row id (1, 2, 3, ...,
 *   never reused). Each node's value is the offset of a **row record**: the
 *   column values packed one after another (8 bytes for an INT; a length byte
 *   plus the bytes for a TEXT), in host byte order.
 *
 * Rows are therefore kept in insertion order, looked up by row id in
 * O(log n), and scanned in order. A WHERE on a column is a full scan.
 *
 * Unless disabled with db_set_sync(), every successful CREATE, INSERT and
 * DELETE is flushed to disk before db_exec() returns.
 */
#ifndef DB_H
#define DB_H

#include <stdbool.h>
#include <stdio.h>

#include "arena.h"
#include "rbtree.h"
#include "squid.h"

/** An open database. */
typedef struct
{
    arena a;         /**< The mapped database file. */
    rb_tree catalog; /**< Tree of tables, keyed by name. */
    bool sync;       /**< Flush after every change (default); see db_set_sync(). */
} db;

/**
 * @brief Opens a database file, creating it if it does not exist.
 * @param d    Database to fill.
 * @param path Path of the database file.
 * @param err  Buffer of ::SQ_ERR_MAX bytes; receives a message on failure.
 * @return 0 on success, -1 on failure (file unreadable, not a squidsql file,
 *         wrong version, in use by another process).
 */
int db_open(db *d, const char *path, char *err);

/**
 * @brief Flushes and closes the database.
 * @param d Database to close; safe to call on a database that failed to open.
 */
void db_close(db *d);

/**
 * @brief Chooses whether every change is flushed to disk immediately.
 *
 * On (the default) a CREATE, INSERT or DELETE is on disk when db_exec()
 * returns, at a cost of milliseconds per statement. Off, flushing happens only
 * in db_close(), which is much faster for bulk loads but loses recent changes
 * if the process dies.
 *
 * @param d  Open database.
 * @param on True to flush after every change.
 */
void db_set_sync(db *d, bool on);

/**
 * @brief Tells whether the file was not closed cleanly the last time.
 * @param d Open database.
 * @return True if the previous session ended abnormally and the data may be
 *         damaged (nothing was checked or repaired).
 */
bool db_was_unclean(const db *d);

/**
 * @brief Executes a parsed statement.
 *
 * Results and confirmations (for example `1 row inserted`) are written to
 * @p out. The checks that need the catalog happen here: the table and columns
 * must exist, literal types must match the column types and an INSERT must
 * supply one value per column. Changes are flushed to disk before returning
 * unless syncing is off (see db_set_sync()).
 *
 * @param d   Database to run against.
 * @param st  Statement produced by parse().
 * @param out Stream that receives the output.
 * @param err Buffer of ::SQ_ERR_MAX bytes; receives a message on failure.
 * @return 0 on success, non-zero on failure.
 */
int db_exec(db *d, const stmt *st, FILE *out, char *err);

/**
 * @brief Prints the name of every table in alphabetical order, one per line.
 * @param d   Database to list.
 * @param out Stream that receives the names.
 */
void db_list_tables(const db *d, FILE *out);

#endif
