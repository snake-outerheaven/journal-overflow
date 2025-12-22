#ifndef SHELL_H
#define SHELL_H

typedef enum ShellStatus
{
        SHELL_OK,
        SHELL_COMMAND_ERROR,
        SHELL_INTERNAL_ERROR,
        SHELL_DEAD,
} ShellStatus;

typedef struct Shell Shell;

Shell *shell_create();
void shell_destroy(Shell *cmd);

void shell_set_prompt(Shell *shell, const char *prompt);
ShellStatus shell_status(const Shell *cmd);

int shell_rum(Shell *cmd);
#endif