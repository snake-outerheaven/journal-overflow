# AGENTS.md - squidsql

Instruções para agentes de código (Claude Code e similares) que trabalham
neste diretório. Para entender a arquitetura, leia
`docs/explanation/arquitetura.md` e `docs/explanation/armazenamento.md`; o
índice da documentação é `docs/index.md`.

## O que é

Banco SQL mínimo escrito em **C11**, em `projects/squidsql/` dentro do
repositório `journal-overflow` (Windows, Visual Studio 18, PowerShell). Os dados
ficam em um arquivo mapeado em memória (HAL → arena → árvore rubro-negra → db).

## Regras de código

- **C11** (`-std=c11 -pedantic`). `stdint.h`, `stdbool.h`, `snprintf` e
  `_Static_assert` são bem-vindos. Código antigo no estilo C89 continua válido;
  não o reescreva só por estilo.
- Formatação: `.clang-format` da raiz (Microsoft, Allman, 4 espaços).
- Funções internas `static`. Erros: retorno `0`/diferente de zero + mensagem em
  `char err[SQ_ERR_MAX]` (sem globais).
- **Offsets, nunca ponteiros, dentro do arquivo.** Toda ligação gravada no
  arquivo é um `uint64_t` contado do byte 0 (0 = nulo). **Nunca guarde o
  resultado de `arena_ptr()` através de uma chamada que aloca** (`arena_alloc`,
  `rb_insert`, `exec_*`): o arquivo pode ser remapeado em outro endereço.
  Guarde o offset e converta de novo depois.
- Mudou o formato em disco (`arena_header`, `table_meta`, nó da árvore, codificação
  de linha)? Aumente `ARENA_VERSION` e atualize `docs/reference/formato-arquivo.md`.
- **Doxygen obrigatório**: todo arquivo tem `@file`/`@brief`; toda função
  (inclusive `static`), `struct`, `enum` e campo tem bloco `/** */` com
  `@brief`, `@param` e `@return`. Campos e enumeradores usam `/**< */`.
  Funções públicas ficam documentadas no `.h`.
- **Documentação segue o Diátaxis** (`docs/tutorial`, `how-to`, `reference`,
  `explanation`). Cada página tem um só propósito; não misture.
- Ao mudar a sintaxe, atualize **juntos**: o código e seus comentários
  Doxygen, `tests/` (scripts e saídas `.out`), `docs/reference/sql.md`,
  `docs/reference/erros.md` e a gramática em `docs/explanation/arquitetura.md`.
- Não adicione dependências nem arquivos fora de `projects/squidsql/` sem
  pedir.

## Compilar e testar

O `cl`/`clang` não estão no PATH. É preciso carregar o ambiente do Visual
Studio antes. No PowerShell, rode a carga e o build **no mesmo `cmd /c`**:

    cmd /c '"C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1 && clang -std=c11 -pedantic -Wall -Wextra -D_CRT_SECURE_NO_WARNINGS -o squidsql.exe main.c parser.c lexer.c db.c arena.c rbtree.c hal_win32.c hal_posix.c'

Com MSVC: `nmake clean`, `nmake`, `nmake test` (mesmo `cmd /c`). O `nmake test`
roda `test_storage.exe` (arena + árvore) e compara a saída de `tests\basic.sql`
e `tests\persist.sql` com `tests\*.out` usando `fc`.

O WSL tem `gcc`: use-o para validar o caminho POSIX da HAL e rodar o teste de
armazenamento com sanitizers (veja `docs/how-to/compilar-e-executar.md`).
Caminhos do Windows ficam em `/mnt/d/...`.

Critério de pronto, todos juntos:

1. clang (comando acima) compila **sem avisos**;
2. `nmake test` passa;
3. o teste de armazenamento passa no WSL com `-fsanitize=address,undefined`;
4. `doxygen Doxyfile` termina sem avisos (o `Doxyfile` trata aviso como erro).
   O Doxygen precisa estar instalado; se não estiver, peça autorização ao
   usuário antes de instalar com `winget`.

Se você mexer em `rbtree.c`, confirme que o teste ainda tem força: quebre
de propósito uma cópia (por exemplo, remova uma rotação de `insert_fixup`) e
veja `rb_check` falhar.

## Armadilhas já encontradas neste ambiente

- **Bash + heredoc com aspas**: um `cat <<'EOF'` com código C contendo `'`
  falhou com "unexpected EOF". Crie arquivos com a ferramenta Write, não com
  heredoc.
- **Comandos dentro de `cmd /c '...'`** são do cmd, não do PowerShell: nada de
  `Select-Object` ali dentro. Faça o pipe do lado de fora: `cmd /c '...' 2>&1 | Select-Object -Last 8`.
- **Executar o `.exe` no cmd** exige `.\squidsql.exe` (o diretório atual não
  está no PATH do cmd).
- **`Remove-Item` no PowerShell tool** foi bloqueado quando a mesma chamada tinha
  `cmd /c` ("system path '/c'") e também com `*` em outro caso. Apague
  artefatos pelo Bash: `rm -f squidsql.exe test_storage.exe *.obj *.db`.
- O MSVC imprime avisos C4996 se faltar `/D_CRT_SECURE_NO_WARNINGS` (já está
  no Makefile).
- O arquivo de banco é aberto com acesso exclusivo: se um teste falhar com
  "cannot open database file", pode haver um `squidsql.exe` antigo vivo.
- Golden files: gere `tests\*.out` com o mesmo redirecionamento do cmd
  (`cmd //c ".\\squidsql.exe test.db tests\\basic.sql > tests\\basic.out"` no
  Bash), senão as quebras de linha (CRLF) divergem e o `fc` reclama.

## Git

- Não commite binários (`*.exe`, `*.obj`, `*.pdb`, `*.ilk`), bancos (`*.db`) nem
  `docs/api/` (saída do Doxygen). O `.gitignore` local já cobre isso; ainda
  assim, apague os artefatos depois de testar.
- Há arquivos `.vs/*` modificados na árvore que não são seus: não os inclua em
  commits.
- Só faça commit quando o usuário pedir. O repositório usa mensagens curtas em
  minúsculas (ex.: `fix: add -> when printing ...`, `port trab exercise to c89 std.`).
- O push por SSH falha neste ambiente (sem chave). O `gh` está autenticado: use
  `git -c credential.helper= -c 'credential.helper=!gh auth git-credential' push -u https://github.com/<dono>/<repo>.git <branch>`.

## Mostrar o programa ao usuário

Para demonstrar, rode no painel de terminal do app (`run_in_terminal`) com
`cwd` em `projects/squidsql`: `.\squidsql.exe demo.db tests\basic.sql`. O REPL
interativo não pode receber digitação do agente; deixe o usuário digitar.

## Mapa rápido de arquivos

    squid.h     tipos e limites          hal.h, hal_win32.c, hal_posix.c   arquivo mapeado
    lexer.c     tokens                   arena.c    alocador por offset
    parser.c    gramática                rbtree.c   árvore rubro-negra no arquivo
    db.c        tabelas, linhas, SQL     main.c     REPL e scripts
    tests/      test_storage.c, scripts .sql e saídas .out

## Histórico (resumo do que foi feito)

1. **Núcleo em memória (C89)**: `squid.h`, lexer, parser, engine, REPL,
   `Makefile`, `tests/basic.sql`. Compilado com `nmake` e com o clang do VS.
2. **Documentação**: primeiro guias de usuário/desenvolvedor, depois migrada
   para o Diátaxis (`docs/`) com todo o código comentado em Doxygen e um
   `Doxyfile` (aviso = erro). O Doxygen não estava instalado: a geração ainda
   não foi validada.
3. **PR #2** (rascunho) com o item 1 e 2.
4. **Armazenamento em disco (C11)**, a pedido do usuário: HAL (Windows e
   POSIX), arena (alocador por offset), árvore rubro-negra no arquivo, `db.c`
   reescrito sobre elas, `INT` de 64 bits, `.sync on|off`, formato versionado.
   Testes: `tests/test_storage.c` (inclusive sob ASan/UBSan no WSL e com
   mutação da árvore para provar que o teste detecta bugs), scripts SQL com
   saída esperada e persistência entre processos.
