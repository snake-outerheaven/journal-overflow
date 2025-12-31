#include <stdio.h>

	/*
	 * Example of 1.9 part of the book, that explain character arrays
	 */


#define MAXLINE 1000

int getline(char*, int);
void copy(char*, char*);


int main()
{
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;

	while((len = getline(line,MAXLINE)) > 0)
		if(len > max)
		{
			max = len;
			copy(longest,line);
		}
	if(max > 0)
		printf("%s\n",longest);
	return 0;
}

int getline(char *s,int lim)
{
	int c, i;

	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;

	if(c == '\n')
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

	while((dest[i] = src[i]) != '\0')
		i++;
}
