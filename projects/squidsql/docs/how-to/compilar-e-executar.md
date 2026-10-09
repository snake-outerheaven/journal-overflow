# Como compilar e executar

Pré-requisito: Visual Studio com as ferramentas de C++ (inclui `cl` e `clang`),
ou qualquer compilador C11 no Linux/macOS.
Todos os comandos rodam na pasta `projects/squidsql`.

## Compilar com MSVC

Em um *Developer Command Prompt*:

    nmake            compila squidsql.exe
    nmake test       compila e roda todos os testes
    nmake clean      apaga objetos, executáveis e arquivos de teste

`nmake test` roda os testes unitários do armazenamento (`test_storage.exe`) e
compara a saída dos scripts `tests\basic.sql` e `tests\persist.sql` com
`tests\basic.out` e `tests\persist.out`. Qualquer diferença interrompe o teste.

## Compilar com clang

Em um *Developer Command Prompt* (ou depois de carregar `vcvars64.bat`):

    clang -std=c11 -pedantic -Wall -Wextra -D_CRT_SECURE_NO_WARNINGS -o squidsql.exe main.c parser.c lexer.c db.c arena.c rbtree.c hal_win32.c hal_posix.c

O resultado esperado é nenhum aviso. Os dois arquivos `hal_*.c` entram sempre:
cada um fica vazio no sistema que não é o seu.

## Compilar no Linux ou macOS

    gcc -std=c11 -pedantic -Wall -Wextra -o squidsql main.c parser.c lexer.c db.c arena.c rbtree.c hal_win32.c hal_posix.c

Para testar o armazenamento com os detectores de erro de memória:

    gcc -std=c11 -fsanitize=address,undefined -g -I. -o test_storage tests/test_storage.c arena.c rbtree.c hal_win32.c hal_posix.c
    ./test_storage /tmp/ts.db

O `Makefile` é para o `nmake`; no Linux/macOS use os comandos acima.

## Compilar a partir do PowerShell comum

O `cl` e o `clang` não estão no PATH de um PowerShell comum. Carregue o ambiente
e compile na mesma chamada do `cmd`:

    cmd /c '"C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1 && nmake'

Ajuste o caminho se o seu Visual Studio estiver em outra edição ou versão.

## Executar

    .\squidsql.exe                      REPL sobre squid.db
    .\squidsql.exe meu.db               REPL sobre meu.db
    .\squidsql.exe meu.db script.sql    executa um script sobre meu.db e sai

O arquivo do banco é criado se não existir. O `.\` é necessário no `cmd` e no
PowerShell. Veja a [referência da linha de comando](../reference/cli.md).

## Carga em lote

Por padrão cada comando é gravado no disco antes de retornar, o que leva alguns
milissegundos. Para carregar muitos dados, comece o script com `.sync off`: a
gravação passa a acontecer só ao fechar (3000 `INSERT`s caem de cerca de 9 s para
60 ms), ao custo de perder as mudanças recentes se o processo morrer.
