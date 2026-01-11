#include <stdio.h>

/*
        How it works to include external variables into local scope.

        The print longest line program will be reapplied here.
*/

#define MAXLINE 10

int max;
char line[MAXLINE];
char longest[MAXLINE];

/* returns the len of words. */

int get_line();

/* copies  from second buffer to first buffer. */

void copy();

/* main function.*/

int main()
{
    extern int max;
    extern char longest[];
    int len;

    max = 0;

    while ((len = get_line()) > 0)
    {
        if (len > max)
        {
            max = len;
            copy();
        }
    }

    if (max > 0)
        printf("%s", longest);

    return 0;
}

int get_line()
{
    int i, c;
    extern char line[];

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;

    if (c == '\n')
    {
        line[i] = c;
        i++;
    }

    line[i] = '\0';

    return i;
}

void copy()
{
    extern char line[], longest[];
    int i;
    i = 0;
    while ((longest[i] = line[i]) != '\0')
        i++;
}
