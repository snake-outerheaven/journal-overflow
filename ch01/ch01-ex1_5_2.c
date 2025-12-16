#include <stdio.h>

/*
        Example from part 1.5.1, about character input output
*/

int main()
{
        int c;

        while (1)
        {
                c = getchar();
                if (c == EOF)
                        break;
                putchar(c);
        }
        return 0;
}