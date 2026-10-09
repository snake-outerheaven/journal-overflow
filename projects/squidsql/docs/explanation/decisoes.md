# Decisões de projeto e limitações

## Por que C11

O projeto nasceu em C89 (como o resto do repositório), mas o armazenamento em
disco pede offsets de 64 bits (`uint64_t`), `_Static_assert`, `snprintf` e
`stdbool.h`, que o C89 não tem. Os módulos antigos continuam válidos em C11 e
foram mantidos como estavam. Compile com `-std=c11 -pedantic`.

## Por que mapear o arquivo em memória

Tira do caminho o código de leitura e escrita em blocos, o cache de páginas e a
serialização: as estruturas são acessadas como memória comum e o sistema
operacional faz o resto. O custo é abrir mão de controlar *quando* cada página
vai para o disco, o que importa para a recuperação após quedas (veja abaixo).
Detalhes em [Armazenamento em disco](armazenamento.md).

## Por que uma HAL

Mapear arquivos é diferente em cada sistema (`CreateFileMapping` no Windows,
`mmap` no POSIX). Isolar isso em quatro funções (`hal_open`, `hal_grow`,
`hal_sync`, `hal_close`) mantém o resto do código idêntico nos dois.

## Por que offsets

O arquivo é remapeado em outro endereço quando cresce e a cada execução.
Ponteiros gravados nele não sobreviveriam. A contrapartida é a disciplina de
nunca guardar um ponteiro através de uma alocação.

## Por que tamanhos fixos para nomes e textos

Nomes (31 caracteres), textos (63) e colunas (8) têm limites fixos (`SQ_*` em
`squid.h`). Isso evita alocação no lexer e no parser e deixa o registro de uma
tabela com tamanho constante. Já o número de tabelas e de linhas é limitado só
pelo disco.

## Por que o parser não consulta o catálogo

Separar sintaxe de semântica deixa o parser testável sem banco e permite
reportar "tabela inexistente" no mesmo lugar para qualquer comando.

## Por que sincronizar a cada comando

É o padrão seguro: um comando que retornou com sucesso já está no disco. Custa
alguns milissegundos por comando (3000 `INSERT`s levam cerca de 9 s) e por isso
existe `.sync off`, que traz a mesma carga para dezenas de milissegundos.

## Limitações conhecidas

- **Não é à prova de queda.** Uma queda no meio de um comando pode corromper o
  arquivo. O banco apenas detecta que o último fechamento não foi limpo.
- **Sem recuperação de espaço.** O arquivo nunca encolhe e blocos livres não são
  unidos.
- **Um escritor.** O arquivo é exclusivo; não há acesso concorrente.
- **Não portável** entre arquiteturas com ordem de bytes diferente.
- Um único predicado `WHERE`, sem `AND`/`OR`, e sem índices: todo `WHERE` varre a tabela.
- Sem `UPDATE`, `DROP TABLE`, `ORDER BY`, `LIMIT`, `JOIN`, funções, `NULL`,
  decimais ou comentários SQL.
- Em um script, o último comando precisa terminar com `;`, senão é descartado.
- A última coluna impressa recebe espaços à direita.
- A divisão de comandos em `main.c` alterna "dentro de texto" a cada `'`. Isso
  funciona com a aspa dobrada `''`, porque dois alternos se cancelam.
- O caminho POSIX da HAL só foi compilado e testado no WSL (gcc), não em macOS.

## Roadmap

1. **Segurança contra quedas**: diário de escrita antecipada ou cópia na escrita.
2. **B+tree** no lugar da rubro-negra, atrás da mesma interface.
3. **Índices secundários** para acelerar `WHERE` fora do id da linha.
4. `UPDATE`, `DROP TABLE`, `AND`/`OR`, `ORDER BY`, `LIMIT`.
5. Chave primária e `NULL`.
