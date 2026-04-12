#include <stdio.h>

int main(void)
{
    char readbuf[10];
    FILE *fp;

    fp = fopen("text.txt", "w+");

    if (!fp)
        return 1;

    fprintf(fp, "Hello file management on C!\n");
    
    rewind(fp);

    puts("Here's what is on the file: ");

    while (fgets(readbuf, sizeof(readbuf), fp))
        printf("%s", readbuf);

    fclose(fp);
    return 0;
}
