#include <stdio.h>

/*
 * Write a function reverse(s) that reverses the character string s. Use it to
 * write a program that reverses its input a line at a time.
 */

#define MAXLINE 100

/*
 * Receives the input string from stdin.
 * Returns the index of characters read from input.
 */
int get_line(char *, int);

/*
 * Reverses the s string
 * Returns the number of characters reversed.
 */
int reverse(char *);

int main()
{
    char s[MAXLINE];

    while (get_line(s, MAXLINE) > 0)
        if (reverse(s) > 0)
            printf("%s", s);

    return 0;
}

int get_line(char *s, int lim)
{
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
    {
        s[i] = '\n';
        i++;
    }
    s[i] = '\0';

    return i;
}

int reverse(char *s)
{
    char temp;
    int i, c, d;

    c = d = 0;

    for (i = 0; s[i] != '\0'; i++)
        ;

    i -= 2; /* Removes \n and \0 as the objective is to reverse it */

    while (i > c)
    {
        temp = s[i];
        s[i] = s[c];
        s[c] = temp;

        c++, i--, d++;
    }

    return d;
}
