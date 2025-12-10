#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
        char buf[BUFSIZ];
        system("cls");

        while (1)
        {
                printf("C:\\Users\\neo\\workspace> ");
                fflush(stdout);
                fgets(buf, sizeof(buf), stdin);
                int end = strlen(buf);
                if (end == 0)
                        continue;
                end--;
                int start = 0;
                while (end >= start && isspace((unsigned char)buf[start]))
                        start++;
                while (start <= end && isspace((unsigned char)buf[end]))
                        end--;
                memmove(buf, buf + start, end - start + 1);
                buf[end - start + 1] = '\0';
                printf("You wrote %s.\n", buf);
        }
}
