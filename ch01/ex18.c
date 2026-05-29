/*
   Write a program to remove trailing blanks and tabs from each line of
   input, and to delete entirely blank lines.
*/

#include <stdio.h>

#define MAXLINE 64
#define LINE_IN 1
#define LINE_OUT 0

int get_line (char ln[], int siz);
void copy (char dest[], char src[]);

int
main (void)
{
  char ln[MAXLINE] = { 0 };
  char sanit_output[MAXLINE] = { 0 };
  int len;
  char c;

  while ((len = get_line (ln, MAXLINE)))
    {
      /*
        TODO: define inline state and outline state here, maybe use memmove to
        move the valid line to the start, and just add a \0 after \n...
      */
    }

  return 0;
}