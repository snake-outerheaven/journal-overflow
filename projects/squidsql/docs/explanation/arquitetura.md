# Arquitetura

Um comando SQL passa por quatro etapas, cada uma em seu módulo:

    texto --lexer--> tokens --parser--> stmt --db_exec--> resultado impresso

| arquivo      | papel                                                             |
| ------------ | ----------------------------------------------------------------- |
| `squid.h`    | tipos compartilhados (`value`, `stmt`, `predicate`) e limites `SQ_*` |
| `lexer.c/h`  | converte texto em `token`s, um por chamada de `lex_next`          |
| `parser.c/h` | descida recursiva; `parse()` preenche um `stmt`                   |
| `db.c/h`     | tabelas em memória e execução (`db_exec`)                         |
| `main.c`     | REPL, leitura de scripts, divisão por `;`, comandos com ponto     |

Os módulos só se conhecem através de `squid.h`: o parser não sabe nada do
banco, e o banco não sabe nada de tokens. Os detalhes de cada função estão na
referência da API gerada pelo Doxygen.

## O `stmt`

O parser entrega um `stmt`, uma struct "plana" que serve a todos os comandos;
os campos usados dependem de `kind` (a tabela está na documentação de `stmt`
em `squid.h`). Como todos os campos têm tamanho fixo, o parser não aloca
memória.

## Lexer

Lê um caractere por vez e devolve um token. Palavras-chave e identificadores
usam a mesma regra; a palavra é comparada em maiúsculas contra a tabela de
palavras reservadas, e o texto do identificador é guardado em minúsculas, o que
torna os nomes insensíveis à caixa. Erros léxicos viram um token `TK_ERROR`
cujo texto é a mensagem.

## Parser

Descida recursiva com um token de lookahead. Cada regra da gramática (veja
[SQL suportado](../reference/sql.md)) é uma função `parse_*` que devolve `0`
ou `-1`, o que permite encadeá-las com `||`. O parser valida apenas a
**sintaxe**.

## Execução

`db_exec` despacha por `stmt.kind` para `exec_create/insert/select/delete`. As
verificações que dependem do catálogo (a tabela existe? os tipos batem?) ficam
aqui. O `WHERE` é resolvido uma vez por `bind_where`, antes do laço sobre as
linhas.

As linhas de uma tabela ficam num vetor de `value` em ordem de linha
(`rows[linha * ncols + coluna]`), que dobra de tamanho quando enche.

## Convenção de erros

Funções que podem falhar devolvem `0` em sucesso e diferente de zero em erro, e
escrevem a mensagem num `char err[SQ_ERR_MAX]` recebido por parâmetro. Não há
variáveis globais de erro.
