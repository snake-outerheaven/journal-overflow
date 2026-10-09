# Como compilar e executar

Pré-requisito: Visual Studio com as ferramentas de C++ (inclui `cl` e `clang`).
Todos os comandos rodam na pasta `projects/squidsql`.

## Compilar com MSVC

Em um *Developer Command Prompt*:

    nmake            compila squidsql.exe
    nmake test       compila e roda tests\basic.sql
    nmake clean      apaga .obj e .exe

## Compilar com clang

Em um *Developer Command Prompt* (ou depois de carregar `vcvars64.bat`):

    clang -std=c89 -pedantic -Wall -Wextra -D_CRT_SECURE_NO_WARNINGS -o squidsql.exe main.c parser.c lexer.c db.c

Use este comando para verificar conformidade com C89: o resultado esperado é
nenhum aviso.

## Compilar a partir do PowerShell comum

O `cl` e o `clang` não estão no PATH de um PowerShell comum. Carregue o ambiente
e compile na mesma chamada do `cmd`:

    cmd /c '"C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1 && nmake'

Ajuste o caminho se o seu Visual Studio estiver em outra edição ou versão.

## Executar

    .\squidsql.exe                 REPL interativo
    .\squidsql.exe script.sql      executa um arquivo e sai

O `.\` é necessário no `cmd` e no PowerShell.
