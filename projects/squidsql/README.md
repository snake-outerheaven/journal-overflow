# squidsql

A tiny in-memory SQL database written in C89. It parses and executes a small
subset of SQL: `CREATE TABLE`, `INSERT`, `SELECT` and `DELETE` with a single
`WHERE` condition.

    squidsql> CREATE TABLE usuarios (id INT, nome TEXT);
    table usuarios created
    squidsql> INSERT INTO usuarios VALUES (1, 'ana');
    1 row inserted
    squidsql> SELECT * FROM usuarios;
     id | nome
    ----+-----
     1  | ana
    (1 row)

## Quick start

From a Visual Studio developer prompt:

    nmake                      build squidsql.exe
    squidsql.exe               interactive REPL
    squidsql.exe script.sql    run a script
    nmake test                 run tests\basic.sql

## Documentation

The docs follow the [Diataxis](https://diataxis.fr/) framework. Start at
[docs/index.md](docs/index.md).

| I want to...            | Read                                                                  |
| ----------------------- | --------------------------------------------------------------------- |
| learn by doing          | [Tutorial: primeiros passos](docs/tutorial/primeiros-passos.md)       |
| build, extend, document | [Compilar](docs/how-to/compilar-e-executar.md), [adicionar comando](docs/how-to/adicionar-comando.md), [gerar docs](docs/how-to/gerar-documentacao.md) |
| look something up       | [SQL](docs/reference/sql.md), [CLI](docs/reference/cli.md), [errors](docs/reference/erros.md) |
| understand the design   | [Arquitetura](docs/explanation/arquitetura.md)                        |
| use the C API           | Doxygen: `doxygen Doxyfile`, then open `docs/api/html/index.html`     |
| work as a coding agent  | [AGENTS.md](AGENTS.md)                                                |

The source is documented with Doxygen (Javadoc-style `/** */` comments).
