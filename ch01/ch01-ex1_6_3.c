#include <stdio.h>

/*
        Line counting program with all stuff we worked from the others.
*/

int main()
{
        size_t counter, lncounter;
        int input;

        counter = lncounter = 0ULL;

        while ((input = getchar()) != EOF)
        {
                putchar(input);
                counter++;
                if (input == '\n')
                        lncounter++;
        }
        printf("chars typed: %zu\t\tnewlines typed: %zu\n", counter, lncounter);
        return 0;
}