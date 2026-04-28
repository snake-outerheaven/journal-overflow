/*
  Experiment to find out what happens when printf’s argument string contains \c,
  where c is some character not listed above.
*/

#include <stdio.h>

int
main()
{
  printf("abba\b\b\b\balala\n");
  return 0;
}

/*
  Answer: \b makes the cursor in stdout go back 1 position, allowing rewriting if desired.
*/
