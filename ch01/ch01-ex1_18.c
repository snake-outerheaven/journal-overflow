#include <stdio.h>

	/*
	 * Write a program to remove trailing blanks and tabs from each line of input,
	 * and to delete entirely blank lines.
	 */
#define MAXLINE 1000


int get_line(char*,int); 
int trim(char*);

int main()
{
	char line[MAXLINE];

	while(get_line(line,MAXLINE) > 0)
		if(trim(line) > 0)
			printf("%s",line);
	return 0;
}

int get_line(char *in, int lim)
{
	int c, i;

	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		in[i] = c;

	if(c == '\n')
	{
		in[i] = '\n';
		i++;
	}

	in[i] = '\0';

	return i;
}

int trim(char *s)
{
    int i;

    for (i = 0; s[i] != '\0'; i++)
        ;

    i--;

    if (i >= 0 && s[i] == '\n')
        i--;

    while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))
        i--;

    if (i < 0)
        return 0;

    s[i + 1] = '\n';
    s[i + 2] = '\0';

    return i + 2;
}
