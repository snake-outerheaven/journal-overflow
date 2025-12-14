#include <Windows.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
        TODO: Add cls, dir. type builtins
 */
int trim(char *buf)
{
        int end = strlen(buf);
        if (end == 0)
                return 1;
        end--;
        int start = 0;
        while (end >= start && isspace((unsigned char)buf[start]))
                start++;
        while (start <= end && isspace((unsigned char)buf[end]))
                end--;
        memmove(buf, buf + start, end - start + 1);
        buf[end - start + 1] = '\0';
        return 0;
}

int main()
{
        char buf[BUFSIZ], cwd[MAX_PATH];

        system("cls");

        while (1)
        {
                GetCurrentDirectoryA(sizeof(cwd), cwd);
                printf("%s> ", cwd);
                fflush(stdout);
                if (!fgets(buf, sizeof(buf), stdin))
                {
                        if (ferror(stdin))
                        {
                                fprintf(stderr, "stdin failed.\n");
                                return 1;
                        }
                        putchar('\n');
                        return 0;
                }
                if (trim(buf))
                        continue;
                if (strncmp(buf, "cd", 2) == 0 && (buf[2] == '\0' || isspace((unsigned char)buf[2])))
                {
                        if (buf[2] == '\0')
                        {
                                printf("%s\n", cwd);
                                continue;
                        }
                        char *path = buf + 3;
                        if (!SetCurrentDirectoryA(path))
                                fprintf(stderr, "Failed to switch directories to %s.\n", path);
                        continue;
                }
                if (strcmp(buf, "cls") == 0)
                {
                        printf("\x1b[2J\x1b[H");
                        fflush(stdout);
                        continue;
                }
                if (strcmp(buf, "exit") == 0)
                {
                        printf("lcmd is shutting off.\n");
                        Sleep(750);
                        exit(0);
                }

                else
                        system(buf);
        }
        return 0;
}
