/**
 * @file main.c
 * @brief Command-line front end: interactive REPL and script runner.
 *
 * Reads statements from stdin (interactive) or from a script file given as
 * the first argument. A statement ends at the first `;` outside a string.
 */

#include <stdio.h>
#include <string.h>

#include "db.h"
#include "parser.h"
#include "squid.h"

/** Size of the input line buffer and of the pending-statement buffer. */
#define BUF_MAX 4096

/**
 * @brief Finds the end of the first complete statement in a buffer.
 * @param buf NUL-terminated pending input.
 * @return Index of the `;` that ends the statement (ignoring any inside a
 *         'string'), or -1 if the statement is not complete yet.
 */
static int find_stmt_end(const char *buf)
{
    int i, in_str = 0;

    for (i = 0; buf[i]; i++)
    {
        if (buf[i] == '\'')
        {
            in_str = !in_str;
        }
        else if (buf[i] == ';' && !in_str)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Tells whether a string contains only whitespace.
 * @param s NUL-terminated string.
 * @return Non-zero if @p s is empty or all whitespace.
 */
static int is_blank(const char *s)
{
    for (; *s; s++)
    {
        if (*s != ' ' && *s != '\t' && *s != '\r' && *s != '\n')
        {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Parses and executes one statement, printing any error to stdout.
 * @param d   Database to run against.
 * @param sql Statement text without its terminating `;`.
 */
static void run_statement(db *d, const char *sql)
{
    stmt st;
    char err[SQ_ERR_MAX];

    if (parse(sql, &st, err) || db_exec(d, &st, stdout, err))
    {
        printf("error: %s\n", err);
    }
}

/**
 * @brief Handles a dot-command (`.tables`, `.help`, `.quit`, `.exit`).
 * @param d    Database, for `.tables`.
 * @param line The input line, starting with `.`.
 * @return Non-zero if the REPL should quit.
 */
static int meta_command(db *d, const char *line)
{
    if (strncmp(line, ".quit", 5) == 0 || strncmp(line, ".exit", 5) == 0)
    {
        return 1;
    }
    if (strncmp(line, ".tables", 7) == 0)
    {
        db_list_tables(d, stdout);
    }
    else if (strncmp(line, ".help", 5) == 0)
    {
        printf("statements end with ';'\n"
               "  CREATE TABLE t (col INT|TEXT, ...);\n"
               "  INSERT INTO t VALUES (1, 'x');\n"
               "  SELECT * | col, ... FROM t [WHERE col op literal];\n"
               "  DELETE FROM t [WHERE col op literal];\n"
               "commands: .tables  .help  .quit\n");
    }
    else
    {
        printf("unknown command: %s", line);
    }
    return 0;
}

/**
 * @brief Reads lines, splits them into statements and runs each one.
 *
 * Input accumulates until a statement is complete, so one statement may span
 * several lines and one line may hold several statements. A trailing
 * statement with no `;` is discarded at end of input.
 *
 * @param d           Database to run against.
 * @param in          Input stream.
 * @param interactive Non-zero to print prompts.
 */
static void repl(db *d, FILE *in, int interactive)
{
    char line[BUF_MAX];
    char buf[BUF_MAX];
    char stmt_buf[BUF_MAX];
    int len = 0, end;

    buf[0] = '\0';
    for (;;)
    {
        if (interactive)
        {
            printf(len == 0 ? "squidsql> " : "      ...> ");
            fflush(stdout);
        }
        if (!fgets(line, sizeof line, in))
        {
            break;
        }
        if (len == 0 && line[0] == '.')
        {
            if (meta_command(d, line))
            {
                break;
            }
            continue;
        }
        if (len + (int)strlen(line) >= BUF_MAX)
        {
            printf("error: statement too long\n");
            buf[0] = '\0';
            len = 0;
            continue;
        }
        strcpy(buf + len, line);
        len += (int)strlen(line);

        while ((end = find_stmt_end(buf)) >= 0)
        {
            memcpy(stmt_buf, buf, (size_t)end);
            stmt_buf[end] = '\0';
            run_statement(d, stmt_buf);

            len -= end + 1;
            memmove(buf, buf + end + 1, (size_t)len + 1);
        }
        if (is_blank(buf))
        {
            buf[0] = '\0';
            len = 0;
        }
    }
}

/**
 * @brief Program entry point.
 * @param argc Argument count.
 * @param argv Optional first argument: a script file to run instead of stdin.
 * @return 0 on success, 1 if the script file cannot be opened.
 */
int main(int argc, char **argv)
{
    db d;
    FILE *in = stdin;

    if (argc > 1)
    {
        in = fopen(argv[1], "r");
        if (!in)
        {
            fprintf(stderr, "squidsql: cannot open %s\n", argv[1]);
            return 1;
        }
    }

    db_init(&d);
    if (in == stdin)
    {
        printf("squidsql 0.1 - type .help for help\n");
    }
    repl(&d, in, in == stdin);
    db_free(&d);

    if (in != stdin)
    {
        fclose(in);
    }
    return 0;
}
