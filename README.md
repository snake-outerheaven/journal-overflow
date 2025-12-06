# Journal Overflow — Soluções comentadas de K&R (2nd Edition)

<img src="assets/c-logo.svg" alt="C logo azul acinzentado" width="96" style="vertical-align:middle">

[![License: GPL v3](https://img.shields.io/badge/license-GPLv3-blue.svg)]()
[![Languages](https://img.shields.io/badge/languages-C-orange.svg)]()

Visão: este repositório contém soluções comentadas, testadas e organizadas para os exercícios do "The C Programming Language" — 2nd edition (Kernighan & Ritchie). O objetivo é ser um recurso didático: código claro, explicações curtas e testes automatizados quando aplicável.

Aviso importante
- Estas são soluções criadas para fins educacionais. Não reproduzem texto protegido do livro.
- Cite Kernighan & Ritchie como fonte das ideias/exercícios quando for relevante.
- Licença: este repositório é distribuído sob a GNU General Public License v3 (GPLv3). Veja o arquivo LICENSE na raiz para detalhes.

Índice rápido
- Visão geral
- Estrutura do repositório
- Convenções de nomeação
- Como compilar e executar (simples)
- Testes e validação
- Guia de contribuição
- Recursos
- Licença

Estrutura proposta
- /ch01/                       -> capítulo 1
  - ch01-ex01/                 -> exercício 1
    - solution.c               -> código fonte do exercício (somente .c por enquanto)
    - README.md                -> explicação da solução (curta)
- /docs/                       -> notas gerais, guia de estilo
- README.md                    -> este arquivo
- LICENSE                      -> GPLv3

Observações importantes
- Sem Makefile por enquanto: cada exercício conterá apenas um arquivo solution.c (conforme solicitado). Se desejar, posteriormente adicionamos Makefiles por exercício.
- Cada solução deve ser didática, bem comentada e preferivelmente acompanhada de um pequeno README explicando a ideia.

Como contribuir
- Abra uma issue antes de submeter um conjunto grande de soluções.
- Para PRs pequenas (um ou poucos exercícios): inclua descrição do exercício (capítulo + número), resumo da abordagem e testes/entradas de exemplo se houver.
- Nomenclatura de diretórios: chNN-exMM (ex.: ch02-ex05).

Recursos
- Página do livro na Amazon (The C Programming Language, 2nd Edition):
  - https://www.amazon.com/Programming-Language-2nd-Brian-Kernighan/dp/0131103628
- Referência/recursos sobre C:
  - https://www.c-language.org/

Licença
- Este repositório é licenciado sob GNU General Public License v3.0 — consulte o arquivo LICENSE para o texto completo.
