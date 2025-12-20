#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define BUFSIZ 1024

void write(HANDLE hOut, const char *s)
{
        DWORD written;
        while (*s)
        {
                WriteFile(hOut, s, 1, &written, NULL);
                s++;
        }
}

DWORD read(HANDLE hIn, char *buf, DWORD max)
{
        char c;
        DWORD read, total;

        read = total = 0;

        while ((total + 1) < max)
        {
                if (!ReadFile(hIn, &c, 1, &read, NULL) || read == 0)
                        break;

                if (c == '\r')
                        continue;

                if (c == '\n')
                        break;

                buf[total++] = c;
        }

        buf[total] = '\0';

        return total;
}

int main()
{
        char input[BUFSIZ], cwd[MAX_PATH];
        HANDLE hIn, hOut;

        hIn = GetStdHandle(STD_INPUT_HANDLE);
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        while (1)
        {
                GetCurrentDirectoryA(MAX_PATH, cwd);
                write(hOut, cwd);
                write(hOut, "\\> ");

                if (read(hIn, input, BUFSIZ) == 0)
                        continue;

                if (lstrcmpA(input, "exit") == 0)
                        break;

                STARTUPINFOA si;
                PROCESS_INFORMATION pi;

                ZeroMemory(&si, sizeof(si));
                ZeroMemory(&pi, sizeof(pi));
                si.cb = sizeof(si);

                if (!CreateProcessA(NULL, input, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
                {
                        write(hOut, "Error executing command.\n");
                        continue;
                }

                WaitForSingleObject(pi.hProcess, INFINITE);

                CloseHandle(pi.hThread);
                CloseHandle(pi.hProcess);
        }
        return 0;
}