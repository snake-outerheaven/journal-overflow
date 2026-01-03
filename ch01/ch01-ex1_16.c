#include <stdio.h>

/*
 * Revise the main routine of the longest-line program so it will correctly
 * print the length of arbitrarily long input lines, and as much as possible of
 * the text.
 */

#define MAXLINE 10

int get_line(char *, int);
void copy(char *, char *);

int main()
{
    int size;
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    size = len = max = 0;

    while ((len = get_line(line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
        size += len;
    }

    if (max > 0)
    {
        printf("Partial or true output: %s\n", longest);
        printf("Arbitrary size of any input: %d\n", size);
    }

    return 0;
}

int get_line(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
    {
        s[i] = c;
        i++;
    }

    s[i] = '\0';

    return i;
}

void copy(char *dest, char *src)
{
    int i;

    i = 0;

    while ((dest[i] = src[i]) != '\0')
        i++;
}

/*
 * The sauce of this exercise is that the getline function is a wrapper around
 * the simple while getchar loop so getline will always read MAXLINE characters
 * of stdin, until EOF, so line is always overwritten over and over and over,
 * until getchar() finds EOF in stdin, printing the partial output that is
 * close.
 */
