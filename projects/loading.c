#include <stdio.h>
#include <windows.h>

int main(void) {
    char spinner[] = { '/', '|', '\\', '-' };
    int i = 0;

    for (int count = 0; count < 20; count++) {
        printf("\rLoading... %c", spinner[i]);
        fflush(stdout);
        Sleep(500); 
        i = (i + 1) % 4;
    }

    printf("\rDone!        \n");
    return 0;
}
