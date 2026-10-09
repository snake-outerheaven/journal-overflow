# Referência: formato do arquivo de banco

Versão do formato: **1**. Todos os inteiros são gravados na ordem de bytes do
computador que criou o arquivo (little-endian em x86 e ARM64); o arquivo **não é
portável** entre arquiteturas com ordem diferente. Todos os campos de 64 bits
ficam alinhados em 8 bytes.

Definições no código: `arena_header` em `arena.h`; `table_meta` e `col_def` em
`db.c`; nó da árvore em `rbtree.c`.

## Visão geral

    offset 0          cabeçalho do arquivo (arena_header)
    header.top        primeiro byte nunca usado
    ...               blocos: [ cabeçalho de 16 bytes | conteúdo ]

Uma posição no arquivo é sempre um **offset** de 64 bits contado a partir do
byte 0. O offset `0` é o cabeçalho, então serve de "nulo".

## Cabeçalho do arquivo (`arena_header`)

| campo          | tipo        | descrição                                            |
| -------------- | ----------- | ---------------------------------------------------- |
| `magic`        | `char[8]`   | `"SQUIDDB"` e um NUL                                 |
| `version`      | `uint32`    | versão do formato (1)                                |
| `clean`        | `uint32`    | 1 se o arquivo foi fechado normalmente; 0 enquanto aberto |
| `file_size`    | `uint64`    | tamanho do arquivo após o último crescimento         |
| `top`          | `uint64`    | offset do primeiro byte nunca alocado                |
| `small_free`   | `uint64[64]`| cabeças das listas de blocos livres de 16, 32, ..., 1024 bytes |
| `large_free`   | `uint64`    | cabeça da lista de blocos livres maiores que 1024 bytes |
| `catalog_root` | `uint64`    | offset da raiz da árvore do catálogo (0 se vazia)    |

Ao abrir, o squidsql recusa o arquivo se `magic` ou `version` não conferem, ou
se `file_size` difere do tamanho real (arquivo truncado ou corrompido).

## Blocos

Todo bloco tem 16 bytes de cabeçalho, seguidos do conteúdo. Um offset aponta
para o **conteúdo**; o cabeçalho está nos 16 bytes anteriores.

| campo  | tipo     | descrição                                       |
| ------ | -------- | ----------------------------------------------- |
| `size` | `uint64` | tamanho do conteúdo (múltiplo de 16, mínimo 16) |
| `tag`  | `uint64` | `0xA110C8ED` alocado; `0xF4EEB10C` livre        |

Um bloco livre guarda, nos primeiros 8 bytes do conteúdo, o offset do próximo
bloco livre da mesma lista. Blocos livres não são unidos; o conteúdo de um
bloco reaproveitado é zerado antes de ser entregue.

## Nó da árvore rubro-negra (48 bytes)

| campo       | descrição                                           |
| ----------- | --------------------------------------------------- |
| `child[0]`  | offset do filho esquerdo (0 se não há)              |
| `child[1]`  | offset do filho direito                             |
| `parent`    | offset do pai (0 na raiz)                           |
| `key`       | palavra de chave (veja abaixo)                      |
| `val`       | palavra de valor (offset de um registro)           |
| `color`     | 0 = vermelho, 1 = preto                             |

## Catálogo

Árvore ordenada pelo **nome da tabela**. Em cada nó, `key` é o offset do nome
(texto terminado em NUL) e `val` é o offset do registro da tabela.

## Registro de tabela (`table_meta`)

| campo        | tipo                | descrição                                    |
| ------------ | ------------------- | -------------------------------------------- |
| `name_off`   | `uint64`            | offset do nome da tabela                     |
| `rows_root`  | `uint64`            | raiz da árvore de linhas (0 se vazia)        |
| `next_rowid` | `uint64`            | id da próxima linha; começa em 1             |
| `nrows`      | `uint64`            | número de linhas                             |
| `ncols`      | `uint32`            | número de colunas (1 a 8)                    |
| `reserved`   | `uint32`            | zero                                         |
| `cols[8]`    | `col_def`           | definições; só as `ncols` primeiras valem    |

`col_def`: `name` (`char[32]`), `type` (`uint32`: 0 = `INT`, 1 = `TEXT`) e
`reserved` (`uint32`, zero).

## Linhas

Árvore ordenada pelo **id da linha** (1, 2, 3, ...; nunca reutilizado, mesmo
depois de `DELETE`). Em cada nó, `key` é o id e `val` é o offset do registro da
linha.

O registro da linha guarda os valores das colunas em sequência, sem separador:

| tipo   | codificação                                                    |
| ------ | -------------------------------------------------------------- |
| `INT`  | 8 bytes, inteiro com sinal de 64 bits                          |
| `TEXT` | 1 byte com o comprimento (0 a 63), depois os bytes do texto    |

## Crescimento

O arquivo começa com 64 KiB e dobra de tamanho sempre que falta espaço. Ele
nunca encolhe: o espaço de linhas e tabelas removidas vai para as listas de
blocos livres e é reaproveitado.
