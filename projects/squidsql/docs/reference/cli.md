# Referência: linha de comando e REPL

## Invocação

    squidsql.exe [banco [script]]

| argumentos        | comportamento                                                           |
| ----------------- | ----------------------------------------------------------------------- |
| (nenhum)          | REPL sobre o arquivo `squid.db` (criado se não existir)                 |
| `banco`           | REPL sobre o arquivo `banco` (criado se não existir)                    |
| `banco script`    | executa os comandos do arquivo `script` sobre `banco`, sem prompt, e sai |

No modo interativo o programa imprime um banner com o nome do banco.

O arquivo do banco é aberto com acesso exclusivo: uma segunda instância que tente
abri-lo falha. Se o arquivo existe mas não é um banco do squidsql, a abertura falha
(veja [Mensagens de erro](erros.md)).

Código de saída: `0` normalmente; `1` se o `script` ou o `banco` não pode ser
aberto (mensagem em `stderr`). Erros de SQL **não** alteram o código de saída.

Se o banco não foi fechado normalmente da última vez (queda, processo morto),
um aviso é impresso em `stderr`:
`warning: <banco> was not closed cleanly; its data may be damaged`.

## Entrada de comandos

- Um comando termina no primeiro `;` fora de um texto entre aspas.
- Um comando pode ocupar várias linhas; o prompt vira `...>` enquanto ele
  está incompleto.
- Uma linha pode conter vários comandos.
- Um comando final sem `;` é descartado ao fim da entrada.
- Um comando acumulado não pode passar de 4095 caracteres.

## Comandos com ponto

Valem apenas no início de um comando novo, ocupam uma linha e não levam `;`.

| comando         | efeito                                                                  |
| --------------- | ----------------------------------------------------------------------- |
| `.tables`       | imprime o nome de cada tabela, em ordem alfabética                      |
| `.sync on`      | grava no disco após cada comando que altera dados (padrão)              |
| `.sync off`     | grava no disco só ao fechar; muito mais rápido, mas arriscado           |
| `.help`         | imprime um resumo da sintaxe                                            |
| `.quit`         | encerra (sinônimo: `.exit`)                                             |

Qualquer outro comando com ponto imprime `unknown command: ...`.

Os dados são gravados no arquivo do banco e persistem entre execuções.

## Saída

Resultados e confirmações vão para a saída padrão. Erros de SQL também, com o
prefixo `error:` (veja [Mensagens de erro](erros.md)).
