# squidsql

A tiny disk-backed SQL database written in C11. It parses and executes a small
subset of SQL: `CREATE TABLE`, `INSERT`, `SELECT` and `DELETE` with a single
`WHERE` condition. Data lives in one memory-mapped file, linked by offsets and
organized as red-black trees.

    squidsql> CREATE TABLE usuarios (id INT, nome TEXT);
    table usuarios created
    squidsql> INSERT INTO usuarios VALUES (1, 'ana');
    1 row inserted
    squidsql> SELECT * FROM usuarios;
     id | nome
    ----+-----
     1  | ana
    (1 row)

Close it, open the same file later, and the rows are still there.

## Quick start

From a Visual Studio developer prompt:

    nmake                          build squidsql.exe
    squidsql.exe meu.db            interactive REPL on the file meu.db
    squidsql.exe meu.db script.sql run a script on meu.db
    nmake test                     storage unit tests + SQL scripts vs expected output

## Documentation

The docs follow the [Diataxis](https://diataxis.fr/) framework. Start at
[docs/index.md](docs/index.md).

| I want to...            | Read                                                                  |
| ----------------------- | --------------------------------------------------------------------- |
| learn by doing          | [Tutorial: primeiros passos](docs/tutorial/primeiros-passos.md)       |
| build, extend, document | [Compilar](docs/how-to/compilar-e-executar.md), [adicionar comando](docs/how-to/adicionar-comando.md), [gerar docs](docs/how-to/gerar-documentacao.md) |
| look something up       | [SQL](docs/reference/sql.md), [CLI](docs/reference/cli.md), [errors](docs/reference/erros.md), [file format](docs/reference/formato-arquivo.md) |
| understand the design   | [Arquitetura](docs/explanation/arquitetura.md), [Armazenamento](docs/explanation/armazenamento.md) |
| use the C API           | Doxygen: `doxygen Doxyfile`, then open `docs/api/html/index.html`     |
| work as a coding agent  | [AGENTS.md](AGENTS.md)                                                |

The source is documented with Doxygen (Javadoc-style `/** */` comments).

## Status

Not crash-safe yet: a power loss in the middle of a statement can corrupt the
file (an unclean shutdown is detected and reported, nothing is repaired). See
[decisões e limitações](docs/explanation/decisoes.md) for the roadmap.
