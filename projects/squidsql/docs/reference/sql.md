# Referência: SQL suportado

## Gramática

    comando  := create | insert | select | delete [ ';' ]

    create   := CREATE TABLE nome '(' coluna { ',' coluna } ')'
    coluna   := nome ( INT | TEXT )
    insert   := INSERT INTO nome VALUES '(' literal { ',' literal } ')'
    select   := SELECT ( '*' | nome { ',' nome } ) FROM nome [ where ]
    delete   := DELETE FROM nome [ where ]
    where    := WHERE nome operador literal

    operador := '=' | '!=' | '<>' | '<' | '<=' | '>' | '>='
    literal  := inteiro | 'texto'

## Comandos

### CREATE TABLE

Cria uma tabela. Falha se o nome já existe ou se há colunas repetidas. Uma
tabela tem de 1 a 8 colunas; o número de tabelas só é limitado pelo disco.

    CREATE TABLE usuarios (id INT, nome TEXT, idade INT);

Saída: `table usuarios created`

### INSERT

Acrescenta uma linha. Os valores seguem a ordem das colunas, em número igual ao
de colunas e com o tipo certo.

    INSERT INTO usuarios VALUES (1, 'ana', 31);

Saída: `1 row inserted`

### SELECT

Lista linhas. `*` seleciona todas as colunas; uma lista de nomes escolhe e
ordena colunas.

    SELECT * FROM usuarios;
    SELECT nome, idade FROM usuarios WHERE idade >= 30;

Saída: cabeçalho, linha de traços, linhas (colunas alinhadas) e `(N rows)`.
As linhas aparecem na ordem de inserção. Um `WHERE` percorre a tabela inteira.

### DELETE

Remove as linhas que satisfazem o `WHERE`; sem `WHERE`, remove todas.

    DELETE FROM usuarios WHERE id = 2;
    DELETE FROM usuarios;

Saída: `N row(s) deleted`

## WHERE

Um único predicado `coluna operador literal`. O literal deve ter o tipo da
coluna. Inteiros se comparam numericamente; textos, byte a byte (diferencia
maiúsculas de minúsculas).

## Tipos

| tipo   | descrição                                                |
| ------ | -------------------------------------------------------- |
| `INT`  | inteiro com sinal de 64 bits                             |
| `TEXT` | até 63 caracteres                                        |

## Literais

- Inteiros: `42`, `-7`. Sem decimais e sem `NULL`.
- Textos: `'ana'`. Uma aspa dentro do texto se escreve dobrada: `'it''s'`.

## Léxico

- Palavras-chave não diferenciam maiúsculas de minúsculas.
- Nomes de tabelas e colunas: letras, dígitos e `_`, sem começar por dígito, até
  31 caracteres; são convertidos para minúsculas.
- Espaços e quebras de linha são livres. Não existem comentários.
