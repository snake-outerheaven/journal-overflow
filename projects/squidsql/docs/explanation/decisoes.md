# Decisões de projeto e limitações

## Por que C89

O restante do repositório é código de estudo em C, e o último commit portou
um exercício para C89. Manter o padrão antigo também é um bom exercício:
declarações no topo do bloco, comentários `/* */`, nada de `snprintf` ou `bool`.
Compilar com `-std=c89 -pedantic` verifica isso.

## Por que tudo tem tamanho fixo

Nomes, textos, colunas e tabelas têm limites fixos (`SQ_*` em `squid.h`). Isso
evita alocação no lexer e no parser, elimina uma classe inteira de vazamentos e
mantém o código curto. O custo: um `stmt` ocupa cerca de 1,5 KB na pilha e
cada célula de texto ocupa 64 bytes mesmo que o texto seja curto. Trocar por
limites dinâmicos está no roadmap.

## Por que em memória

O foco desta primeira versão é o caminho texto → parser → execução. O formato
em disco (páginas, cabeçalho, versionamento) é um projeto à parte e entra
depois, quando o catálogo e os tipos estiverem estáveis.

## Por que o parser não consulta o catálogo

Separar sintaxe de semântica deixa o parser testável sem banco e permite
reportar "tabela inexistente" no mesmo lugar para qualquer comando.

## Limitações conhecidas

- Os dados não são persistidos.
- Um único predicado `WHERE`; sem `AND`/`OR`.
- Sem `UPDATE`, `DROP TABLE`, `ORDER BY`, `LIMIT`, `JOIN`, funções, `NULL`,
  decimais ou comentários SQL.
- Em um script, o último comando precisa terminar com `;`, senão é descartado.
- A última coluna impressa recebe espaços à direita.
- A divisão de comandos em `main.c` alterna "dentro de texto" a cada `'`. Isso
  funciona com a aspa dobrada `''`, porque dois alternos se cancelam.

## Roadmap

1. Persistência em disco (`.save`/`.open`).
2. `UPDATE`, `DROP TABLE`, `AND`/`OR`, `ORDER BY`, `LIMIT`.
3. Chave primária e índice (B-tree).
4. Limites dinâmicos.
5. Teste automatizado comparando a saída com um arquivo esperado.
