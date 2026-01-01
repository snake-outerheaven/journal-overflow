#include <stdio.h>

	/*
	 * Write a program to print all input lines that are longer than 80 characters.
	 */

#define MAXLINE 100

typedef enum state
{
	STATE_READ,
	STATE_EOF,
	STATE_PRINT
} State;


/* returns the index of characters written
 * receives the input char buffer plus a limiter integer and a address of a char variable so
 * the main routine can always check the current character inside the while getchar loop on this function
 * plus an int address to always get the arbitrary size of input.
 */
int get_line(char*,int,char*,int*); 

/*
 * receives the input buffer and output buffer.
 */
void copy(char*,char*); 

/*
 * receives the output buffer.
 */ 
void print_line(char*);


int main()
{	
	char inbuf[MAXLINE], oubuf[MAXLINE], current;
	int len, tot;
	State state;

	len = tot = 0;
	state = STATE_READ;

	while(state != STATE_EOF)
	{
		switch(state)
		{
			case STATE_READ:
				len = get_line(inbuf,MAXLINE,&current,&tot);
				if(len > 80 && current == '\n')
				{
					copy(inbuf,oubuf);
					state = STATE_PRINT;
				}
				if(current == EOF)
					state = STATE_EOF;
				break;

			case STATE_PRINT:
				print_line(oubuf);
				state = STATE_READ;
				break;
			
			default:
				puts("Undefined behaviour lies beyond here!");
				break;
		}
	}
	
	printf("Arbitrary size of input: %d\n", tot);
	puts("Program terminated with EOF.");
	return 0;
}


int get_line(char *buf, int lim, char *current, int *tot)
{
    int c, i;

    i = c = *current = 0;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        buf[i] = c;
	(*tot)++;
    }

    if (c == '\n')
    {
        buf[i] = c;
        i++;
        *current = '\n';
    }
    else if (c == EOF)
        *current = EOF;
    else if(i > 0)
        *current = buf[i - 1];

    buf[i] = '\0';
    return i;
}

void copy(char *src, char *dest)
{
    int i = 0;
    while ((dest[i] = src[i]) != '\0')
        i++;
}

void print_line(char *buf)
{
    int i = 0;
    while (buf[i] != '\0')
    {
        putchar(buf[i]);
        i++;
    }
}
