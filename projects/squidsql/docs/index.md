# squidsql {#mainpage}

squidsql é um banco de dados SQL minúsculo, em memória, escrito em C89. Ele
lê um subconjunto pequeno de SQL (`CREATE TABLE`, `INSERT`, `SELECT`,
`DELETE`) e executa os comandos num REPL ou a partir de um script.

Esta documentação segue o [Diátaxis](https://diataxis.fr/): cada página tem
um único propósito, e você escolhe pelo que precisa.

| Eu quero...                              | Seção                                   |
| ---------------------------------------- | --------------------------------------- |
| aprender usando o programa pela 1ª vez   | **Tutorial**                            |
| resolver uma tarefa concreta             | **Guias práticos** (how-to)             |
| consultar um fato exato                  | **Referência**                          |
| entender por que ele é assim             | **Explicação**                          |

## Tutorial

- [Primeiros passos](tutorial/primeiros-passos.md)

## Guias práticos

- [Compilar e executar](how-to/compilar-e-executar.md)
- [Adicionar um comando SQL](how-to/adicionar-comando.md)
- [Gerar esta documentação](how-to/gerar-documentacao.md)

## Referência

- [SQL suportado](reference/sql.md)
- [Linha de comando e REPL](reference/cli.md)
- [Mensagens de erro](reference/erros.md)
- API em C: gerada pelo Doxygen a partir do código-fonte (veja os arquivos
  `squid.h`, `lexer.h`, `parser.h` e `db.h`).

## Explicação

- [Arquitetura](explanation/arquitetura.md)
- [Decisões de projeto e limitações](explanation/decisoes.md)

## Para agentes de código

O arquivo `AGENTS.md`, na raiz do projeto, reúne as regras e as armadilhas do
ambiente para agentes automatizados.
