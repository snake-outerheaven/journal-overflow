#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int trim(char *);

int main(void)
{
    char input[50];
    /* int guess; */
    int secret;

    srand(time(NULL));
    secret = rand() % 100 + 1;

    printf("Dear player, this is a guessing game designed to test my skills "
           "after juggling a bit of K&R first chapter.\nI wish you have as "
           "much fun as i had writing this game :)\n");

    printf("\n\n\n\n");

    printf("Please, write a guess between 1 and 100 please: ");

    if (!fgets(input, sizeof(input), stdin) || trim(input))
        exit(EXIT_FAILURE);

    printf("You entered %s.\n", input);
    printf("The secret is %d.\n", secret);

    return 0;
}

int trim(char *buf)
{
    size_t start, end;

    start = 0;
    end = strlen(buf);

    if (end == 0)
        return 1;

    end--;

    while (start <= end && isspace((unsigned char)buf[start]))
        start++;

    while (end >= start && isspace((unsigned char)buf[end]))
        end--;

    memmove(buf, buf + start, end - start + 1);

    buf[end - start + 1] = '\0';

    return 0;
}
