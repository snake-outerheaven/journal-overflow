#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "shell.h"

#define SHELL_BUFSIZE 1024

typedef struct ShellHistoryNode ShellHistoryNode;

struct ShellHistoryNode
{
    char *cmd;
    ShellHistoryNode *prev;
    ShellHistoryNode *next;
};

typedef struct ShellHistoryList
{
    size_t size;
    ShellHistoryNode *head;
    ShellHistoryNode *tail;
} ShellHistoryList;

struct Shell
{
    char *prompt;
    ShellStatus status;

    HANDLE hStdin;
    HANDLE hStdout;
    HANDLE hStderr;

    ShellHistoryList history;
};

static void *shell_alloc(SIZE_T size)
{
    return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

static void shell_free(void *ptr)
{
    if (ptr)
        HeapFree(GetProcessHeap(), 0, ptr);
}

Shell *shell_create(void)
{
    Shell *shell = (Shell *)shell_alloc(sizeof(Shell));
    if (!shell)
        return NULL;

    shell->status = SHELL_OK;
    shell->hStdin = GetStdHandle(STD_INPUT_HANDLE);
    shell->hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    shell->hStderr = GetStdHandle(STD_ERROR_HANDLE);

    return shell;
}

void shell_destroy(Shell *shell)
{
    if (!shell)
        return;

    shell_free(shell->prompt);
    shell_free(shell);
}

void shell_set_prompt(Shell *shell, const char *prompt)
{
    if (!shell)
        return;

    shell_free(shell->prompt);
    shell->prompt = NULL;

    if (!prompt)
        return;

    SIZE_T len = lstrlenA(prompt) + 1;
    shell->prompt = (char *)shell_alloc(len);
    if (shell->prompt)
        lstrcpyA(shell->prompt, prompt);
}

ShellStatus shell_status(const Shell *shell)
{
    if (!shell)
        return SHELL_INTERNAL_ERROR;

    return shell->status;
}

int shell_run(Shell *shell)
{
    if (!shell)
        return -1;

    shell->status = SHELL_OK;
    return 0;
}
