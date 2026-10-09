# Referência: mensagens de erro

Todo erro de SQL é impresso como `error: <mensagem>`, e o programa continua.

## Léxicos

Aparecem como `lexical error: <causa>`.

| causa                  | quando                                              |
| ---------------------- | --------------------------------------------------- |
| `unexpected character` | caractere que não pertence à linguagem (ex.: `@`, `!` sozinho) |
| `unterminated string`  | aspa de abertura sem aspa de fechamento             |
| `string too long`      | texto com 64 caracteres ou mais                     |
| `identifier too long`  | palavra com 64 caracteres ou mais                   |
| `number too long`      | mais de 62 dígitos                                  |
| `number out of range`  | não cabe em um `long`                               |

## Sintáticos

| mensagem                                              | quando                                   |
| ----------------------------------------------------- | ---------------------------------------- |
| `syntax error: expected X near 'Y'`                   | o token `Y` não era o esperado `X`       |
| `syntax error: expected X, got end of input`          | o comando acabou antes da hora           |
| `empty statement`                                     | `;` sem nenhum comando                   |
| `name 'n' is too long (max 31)`                       | nome de tabela/coluna acima de 31 caracteres |
| `too many columns (max 8)` / `too many values (max 8)` | acima de `SQ_MAX_COLS`                   |

## De execução

| mensagem                                                | quando                                     |
| ------------------------------------------------------- | ------------------------------------------ |
| `no such table: t`                                      | a tabela não existe                        |
| `no such column: c`                                     | a coluna não existe na tabela              |
| `table already exists: t`                               | `CREATE TABLE` com nome em uso             |
| `duplicate column: c`                                   | coluna repetida no `CREATE TABLE`          |
| `too many tables (max 16)`                              | catálogo cheio                             |
| `table t has N columns but M values were supplied`      | `INSERT` com número errado de valores      |
| `type mismatch: column c is INT` (ou `TEXT`)            | literal de tipo diferente do da coluna     |
| `out of memory`                                         | falha de alocação no `INSERT`              |
