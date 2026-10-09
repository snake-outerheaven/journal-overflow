/**
 * @file parser.h
 * @brief Syntactic analysis: turns SQL text into a ::stmt.
 */
#ifndef PARSER_H
#define PARSER_H

#include "squid.h"

/**
 * @brief Parses a single SQL statement.
 *
 * The statement may end with an optional `;`. Anything after it is a syntax
 * error. The parser checks syntax only; whether tables and columns exist, and
 * whether types match, is checked later by db_exec().
 *
 * @param sql NUL-terminated statement text.
 * @param out Receives the statement. It is zeroed first, so it is always safe
 *            to inspect, but only meaningful when the call succeeds.
 * @param err Buffer of at least ::SQ_ERR_MAX bytes; receives the message on
 *            failure.
 * @return 0 on success, non-zero on a lexical or syntax error.
 */
int parse(const char *sql, stmt *out, char *err);

#endif
