#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAXINPUT 50
#define MAX 100
#define MIN 1
#define BAD_TRIM 1
#define GOOD_TRIM 0

#define BAD_PARSE 1
#define GOOD_PARSE 0

int trim(char *);
int parse(char *, int *);
void Sleep(int);

int main(void)
{
    char input[MAXINPUT];
    int guess;
    int tries;
    int secret;

    srand(time(NULL));
    secret = rand() % MAX + MIN;

    tries = 0;

    printf("Dear player, this is a guessing game designed to test my skills "
           "after juggling a bit of K&R first chapter.\nI wish you have as "
           "much fun as i had writing this game :)\n");

    printf("\n\n\n\n");

    while (1)
    {
        tries++;
        printf("Please, write a guess between %d and %d (type quit to quit): ",
               MIN, MAX);

        if (!fgets(input, sizeof(input), stdin) || trim(input) == BAD_TRIM)
            continue;

        if (!strcmp(input, "quit"))
	{
		puts("Quitting...");
		Sleep(1000);
		break;
	}

        if (parse(input, &guess) == BAD_PARSE)
        {
            fprintf(stderr,
                    "It wasn't possible to parse the input \"%s\" to a integer.\n",
                    input);
        }

        if (guess > MAX)
        {
            printf("%d is bigger than the max number %d.\n", guess, MAX);
            continue;
        }
        else if (guess < MIN)
        {
            printf("%d is lower than the min number %d.\n", guess, MIN);
            continue;
        }

        if (guess > secret)
            printf("Too high!\n");

        else if (guess < secret)
            printf("Too low!\n");

        else
        {
            printf("You got it with %d tries!\n", tries);
            break;
        }
    }

    return 0;
}

int trim(char *buf)
{
    size_t start, end;

    start = 0;
    end = strlen(buf);

    if (end == 0)
        return BAD_TRIM;

    end--;

    while (start <= end && isspace((unsigned char)buf[start]))
        start++;

    while (end >= start && isspace((unsigned char)buf[end]))
        end--;

    memmove(buf, buf + start, end - start + 1);

    /* buf[end - start + 1] = '\0'; */

    *(buf + (end - start + 1)) = '\0'; /*  pointer notation. */

    return GOOD_TRIM;
}

int parse(char *buf, int *out)
{
    char *check;

    *out = (int)strtoul(buf, &check, 10);

    if (check == buf)
        return BAD_PARSE;
    else
        return GOOD_PARSE;
}

void Sleep(int tm)
{
	usleep(tm * 1000);
}
