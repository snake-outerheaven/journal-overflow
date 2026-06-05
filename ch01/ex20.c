/*
   Write a program detab that replaces tabs in the input with the proper
   number of blanks to space to the next tab stop. Assume a fixed set of tab
   stops, say every n columns. Should n be a variable or a symbolic parameter?
*/

#include <stdio.h>

#define MAXLEN 300
#define TABSIZE 4

#define IN 1
#define OUT 0

int get_line (char[], int);
int detab (char[]);