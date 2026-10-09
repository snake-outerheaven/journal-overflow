# Arquitetura

Um comando SQL passa por quatro etapas; a última grava no armazenamento em disco.

    texto --lexer--> tokens --parser--> stmt --db_exec--> armazenamento

| arquivo        | papel                                                             |
| -------------- | ----------------------------------------------------------------- |
| `squid.h`      | tipos compartilhados (`value`, `stmt`, `predicate`) e limites `SQ_*` |
| `lexer.c/h`    | converte texto em `token`s, um por chamada de `lex_next`          |
| `parser.c/h`   | descida recursiva; `parse()` preenche um `stmt`                   |
| `db.c/h`       | tabelas e linhas sobre o armazenamento; execução (`db_exec`)      |
| `rbtree.c/h`   | árvore rubro-negra cujos nós vivem no arquivo                     |
| `arena.c/h`    | alocador de blocos dentro do arquivo mapeado                      |
| `hal.h`, `hal_win32.c`, `hal_posix.c` | arquivo mapeado em memória, por sistema operacional |
| `main.c`       | REPL, leitura de scripts, divisão por `;`, comandos com ponto     |

As dependências vão em uma só direção: `main` → `db` → `rbtree` → `arena` →
`hal`. O parser só conhece `squid.h`: não sabe nada do banco, e o banco não sabe
nada de tokens. O detalhe do armazenamento está em
[Armazenamento em disco](armazenamento.md).

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

- O **catálogo** é uma árvore rubro-negra ordenada pelo nome da tabela.
- Cada tabela tem uma árvore de **linhas** ordenada por id crescente.
- Uma linha é um registro compacto, decodificado para `value[]` quando lida.

`INSERT` e `DELETE` mexem só nas árvores e no alocador; `SELECT` percorre a
árvore em ordem. Qualquer `WHERE` é uma varredura completa.

## Convenção de erros

Funções que podem falhar devolvem `0` em sucesso e diferente de zero em erro, e
escrevem a mensagem num `char err[SQ_ERR_MAX]` recebido por parâmetro. Não há
variáveis globais de erro. As funções de armazenamento que não têm como
descrever o erro (como `arena_alloc`) devolvem `0` e quem chama monta a mensagem.
