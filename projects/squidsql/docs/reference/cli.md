# Referência: linha de comando e REPL

## Invocação

    squidsql.exe [arquivo]

| argumento | comportamento                                                      |
| --------- | ------------------------------------------------------------------ |
| (nenhum)  | modo interativo: imprime o banner e o prompt, lê da entrada padrão |
| `arquivo` | executa os comandos do arquivo, sem banner nem prompt, e sai       |

Código de saída: `0` normalmente; `1` se o arquivo não pode ser aberto
(mensagem em `stderr`). Erros de SQL **não** alteram o código de saída.

## Entrada de comandos

- Um comando termina no primeiro `;` fora de um texto entre aspas.
- Um comando pode ocupar várias linhas; o prompt vira `...>` enquanto ele
  está incompleto.
- Uma linha pode conter vários comandos.
- Um comando final sem `;` é descartado ao fim da entrada.
- Um comando acumulado não pode passar de 4095 caracteres.

## Comandos com ponto

Valem apenas no início de um comando novo, ocupam uma linha e não levam `;`.

| comando   | efeito                                  |
| --------- | --------------------------------------- |
| `.tables` | imprime o nome de cada tabela           |
| `.help`   | imprime um resumo da sintaxe            |
| `.quit`   | encerra (sinônimo: `.exit`)             |

Qualquer outro comando com ponto imprime `unknown command: ...`.

## Saída

Resultados e confirmações vão para a saída padrão. Erros de SQL também, com o
prefixo `error:` (veja [Mensagens de erro](erros.md)).
