# AGENTS.md - squidsql

Instruções para agentes de código (Claude Code e similares) que trabalham
neste diretório. Para entender a arquitetura, leia
`docs/explanation/arquitetura.md`; o índice da documentação é `docs/index.md`.

## O que é

Banco SQL mínimo em memória, escrito em **C89**, em `projects/squidsql/` dentro
do repositório `journal-overflow` (Windows, Visual Studio 18, PowerShell).

## Regras de código

- C89 estrito: declarações no topo do bloco, comentários `/* */`, nada de
  `//`, `snprintf`, `bool` ou `for (int i...)`.
- Formatação: `.clang-format` da raiz (Microsoft, Allman, 4 espaços).
- Funções internas `static`. Erros: retorno `0`/diferente de zero + mensagem em
  `char err[SQ_ERR_MAX]` (sem globais).
- **Doxygen obrigatório**: todo arquivo tem `@file`/`@brief`; toda função
  (inclusive `static`), `struct`, `enum` e campo tem bloco `/** */` com
  `@brief`, `@param` e `@return`. Campos e enumeradores usam `/**< */`.
  Funções públicas ficam documentadas no `.h`.
- **Documentação segue o Diátaxis** (`docs/tutorial`, `how-to`, `reference`,
  `explanation`). Cada página tem um só propósito; não misture.
- Ao mudar a sintaxe, atualize **juntos**: o código e seus comentários
  Doxygen, `tests/`, `docs/reference/sql.md`, `docs/reference/erros.md` e a
  gramática em `docs/explanation/arquitetura.md`.
- Não adicione dependências nem arquivos fora de `projects/squidsql/` sem
  pedir.

## Compilar e testar

O `cl`/`clang` não estão no PATH. É preciso carregar o ambiente do Visual
Studio antes. No PowerShell, rode a carga e o build **no mesmo `cmd /c`**:

    cmd /c '"C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1 && clang -std=c89 -pedantic -Wall -Wextra -D_CRT_SECURE_NO_WARNINGS -o squidsql.exe main.c parser.c lexer.c db.c'

Alternativa com MSVC: `nmake` / `nmake test` / `nmake clean` (mesmo `cmd /c`).

Critério de pronto: compila **sem avisos** com o comando do clang acima,
`squidsql.exe tests\basic.sql` imprime o resultado esperado (mensagens em
`docs/reference/erros.md`) e `doxygen Doxyfile` termina sem avisos (o
`Doxyfile` trata aviso como erro). O Doxygen precisa estar instalado; se não
estiver, peça autorização ao usuário antes de instalar com `winget`.

## Armadilhas já encontradas neste ambiente

- **Bash + heredoc com aspas**: um `cat <<'EOF'` com código C contendo `'`
  falhou com "unexpected EOF". Crie arquivos com a ferramenta Write, não com
  heredoc.
- **Comandos dentro de `cmd /c '...'`** são do cmd, não do PowerShell: nada de
  `Select-Object` ali dentro. Faça o pipe do lado de fora: `cmd /c '...' 2>&1 | Select-Object -Last 8`.
- **Executar o `.exe` no cmd** exige `.\squidsql.exe` (o diretório atual não
  está no PATH do cmd).
- **`Remove-Item` junto de `cmd /c` na mesma chamada** foi bloqueado
  ("system path '/c'"). Separe: compile numa chamada e apague artefatos em
  outra (ex.: `rm -f squidsql.exe *.obj` no Bash).
- O PowerShell tool imprime avisos C4996 no MSVC se faltar
  `/D_CRT_SECURE_NO_WARNINGS` (já está no Makefile).

## Git

- Não commite binários (`*.exe`, `*.obj`, `*.pdb`, `*.ilk`) nem `docs/api/`
  (saída do Doxygen). O `.gitignore` local já cobre isso; ainda assim, apague
  os artefatos depois de testar.
- Há arquivos `.vs/*` modificados na árvore que não são seus: não os inclua em
  commits.
- Só faça commit quando o usuário pedir. O repositório usa mensagens curtas em
  minúsculas (ex.: `fix: add -> when printing ...`, `port trab exercise to c89 std.`).

## Mostrar o programa ao usuário

Para demonstrar, rode no painel de terminal do app (`run_in_terminal`) com
`cwd` em `projects/squidsql`: `.\squidsql.exe tests\basic.sql`. O REPL
interativo não pode receber digitação do agente; deixe o usuário digitar.

## Mapa rápido de arquivos

    squid.h    tipos e limites         parser.c   gramática
    lexer.c    tokens                  db.c       execução e catálogo
    main.c     REPL e scripts          tests/     scripts .sql de regressão

## Passo a passo do que foi feito na criação (histórico)

1. Inspecionei o repositório: projetos em C com `nmake`/`cl`, último commit
   portando código para C89 → escolhi C89 em `projects/squidsql/`.
2. Defini o escopo mínimo: `CREATE TABLE`, `INSERT`, `SELECT`, `DELETE`, um
   `WHERE`, tipos `INT`/`TEXT`, tudo em memória.
3. Escrevi `squid.h` (tipos), `lexer`, `parser`, `db`, `main`, `Makefile`,
   `tests/basic.sql` e o README.
4. Localizei o Visual Studio com `vswhere` e carreguei o `vcvars64.bat`.
5. Compilei com `nmake`, corrigi o alinhamento da linha separadora do
   `SELECT` e silenciei os avisos C4996.
6. Compilei também com o clang do VS (`-std=c89 -pedantic -Wall -Wextra`):
   zero avisos, mesma saída.
7. Rodei `tests/basic.sql` no painel de terminal para demonstração.
8. Escrevi a primeira documentação (guias de usuário e desenvolvedor, e este arquivo).
9. A pedido do usuário, migrei a documentação para o Diátaxis (`docs/`),
   comentei todo o código-fonte em Doxygen e criei o `Doxyfile` (aviso =
   erro). O Doxygen não estava instalado, então a geração ainda não foi
   validada; a conformidade C89 foi rechecada com clang.
