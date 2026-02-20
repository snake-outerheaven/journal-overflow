#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAXINPUT 100
#define MAX 100
#define MIN 1

#define BAD_TRIM 1
#define GOOD_TRIM 0

#define BAD_PARSE 1
#define GOOD_PARSE 0

#define BAD_SAVE 1
#define GOOD_SAVE 0

int trim(char *);
int parse(char *, int *);
int save(const int, const int);
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
            fprintf(
                stderr,
                "It wasn't possible to parse the input \"%s\" to a integer.\n",
                input);
            continue;
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

    if (save(tries, secret) == BAD_SAVE)
        puts("It wasn't possible to save this run.");

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
    long val;

    val = strtol(buf, &check, 10);

    if (check == buf || *check != '\0')
        return BAD_PARSE;

    if (val < MIN || val > MAX)
        return BAD_PARSE;

    *out = (int)val;

    return GOOD_PARSE;
}

void Sleep(int tm)
{
    usleep(tm * 1000);
}

int save(const int tries, const int random)
{
    char timestamp[MAXINPUT];
    time_t now;
    struct tm *tm_info;
    FILE *fp;

    time(&now);
    tm_info = localtime(&now);

    strftime(timestamp, sizeof(timestamp), "%d/%m/%Y %H:%M:%S", tm_info);

    fp = fopen("guessing_game_log.txt", "a");

    if (!fp)
        return BAD_SAVE;

    fprintf(fp, "[%s] tries=%d random=%d\n", timestamp, tries, random);

    fclose(fp);

    return GOOD_SAVE;
}
