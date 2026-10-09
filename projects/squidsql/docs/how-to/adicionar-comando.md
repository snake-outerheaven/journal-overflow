# Como adicionar um comando SQL

Exemplo: adicionar `DROP TABLE t;`. A receita vale para qualquer comando novo.
Entenda o fluxo antes em [Arquitetura](../explanation/arquitetura.md).

1. **Token.** Em `lexer.h`, acrescente `TK_DROP` ao enum `tk_type`. Em
   `lexer.c`, acrescente `{"DROP", TK_DROP}` à tabela `keywords[]`.

2. **Tipo de comando.** Em `squid.h`, acrescente `STMT_DROP` ao enum
   `stmt_kind`. Se precisar de campos novos em `stmt`, documente-os com
   `/**< ... */`.

3. **Parser.** Em `parser.c`, escreva `parse_drop(parser *p, stmt *st)`
   seguindo o padrão das outras: `st->kind = ...;`, depois uma cadeia de
   `advance`/`expect`/`take_ident` ligada por `||`, devolvendo `0` ou `-1`.
   Registre-a com um `case TK_DROP:` em `parse()`.

4. **Execução.** Em `db.c`, escreva `exec_drop(db *d, const stmt *st, FILE *out, char *err)`
   e registre-a com um `case STMT_DROP:` em `db_exec()`. Valide o que depende do
   catálogo aqui (a tabela existe?), nunca no parser.

5. **Teste.** Acrescente a `tests\basic.sql` um caso de sucesso e um de erro,
   atualize a saída esperada `tests\basic.out` (depois de conferir à mão que a
   nova saída está certa) e rode `nmake test`.

6. **Documentação.** Atualize [SQL suportado](../reference/sql.md), as
   [mensagens de erro](../reference/erros.md) e a gramática em
   [Arquitetura](../explanation/arquitetura.md). Cada função nova precisa de um
   bloco `/** ... */` com `@brief`, `@param` e `@return`, senão o Doxygen avisa.

7. **Verifique.** Compile com clang (`-std=c11 -pedantic -Wall -Wextra`): zero
   avisos. Se o comando altera dados, lembre-se de que o arquivo pode ser
   remapeado a cada alocação: use offsets, e chame `flush` ao final.
