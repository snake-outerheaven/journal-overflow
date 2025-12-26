#include <stdio.h>

/*
        Write a program to print a histogram of the frequencies of different characters in its input.
        This is exercise 1-14
*/

#define LETTERS 52

typedef enum state
{
        READ_STATE,
        CLASSIFY_STATE,
        EOF_STATE,
        PRINT_STATE,
} State;

int main()
{
        State state;
        int c;
        int i;
        int freq[LETTERS];

        state = READ_STATE;

        for (i = 0; i < LETTERS; i++)
                freq[i] = 0;

        while (state != PRINT_STATE)
        {
                switch (state)
                {
                case READ_STATE:
                        c = getc(stdin);

                        if (c == EOF)
                                state = EOF_STATE;
                        else
                                state = CLASSIFY_STATE;
                        break;

                case CLASSIFY_STATE:
                        if (c >= 'a' && c <= 'z')
                                freq[c - 'a']++;
                        else if (c >= 'A' && c <= 'Z')
                                freq[c - 'A']++;
                        state = READ_STATE;
                        break;

                case EOF_STATE:
                        state = PRINT_STATE;
                        break;

                default:
                        printf("Undefined behavior awaits here.\n");
                        break;
                }
        }
}