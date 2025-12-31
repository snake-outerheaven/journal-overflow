#include <stdio.h>

/*
        Write a program to print a histogram of the frequencies of different characters in its input.
	Exercise 1-14 (K&R)
*/

#define LETTERS 52

typedef enum state { READ_STATE, CLASSIFY_STATE, EOF_STATE, PRINT_STATE } State;

int main() {
  State state;
  int c;
  int i, i2;
  int freq[LETTERS];

  state = READ_STATE;

  for (i = 0; i < LETTERS; i++)
    freq[i] = 0;

  while (state != PRINT_STATE) {
    switch (state) {
    case READ_STATE:
      c = getc(stdin);
      if (c == EOF)
        state = EOF_STATE;
      else
        state = CLASSIFY_STATE;
      break;

    case CLASSIFY_STATE:
      if (c >= 'A' && c <= 'Z')
        freq[c - 'A']++; /* 0..25 */
      else if (c >= 'a' && c <= 'z')
        freq[c - 'a' + 26]++; /* 26..51 */
      state = READ_STATE;
      break;

    case EOF_STATE:
      state = PRINT_STATE;
      break;

    case PRINT_STATE:
      break;

    default:
      printf("Undefined behaviour lives here.\n");
      break;
    }
  }

  for (i = 0; i < 26; i++) {
    printf("%c -> ", 'A' + i);
    for (i2 = 0; i2 < freq[i]; i2++)
      printf("* ");
    putchar('\n');
  }

  putchar('\n');

  for (i = 0; i < 26; i++) {
    printf("%c -> ", 'a' + i);
    for (i2 = 0; i2 < freq[i + 26]; i2++)
      printf("* ");
    putchar('\n');
  }

  return 0;
}

/*
        Previous versions of this code were failing because i did something
   real stupid

        i basically failed to realize the freq array had the uppercase base.
*/
