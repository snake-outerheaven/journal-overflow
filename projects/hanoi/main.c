#include "helper.h"
#include "stack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    int array[10];
    int size = sizeof(array) / sizeof(array[0]);
    int *stackarray;
    Stack *s;
    size_t stacksize;
    IntArray a = {array, size};

    s = init();

    for (i = 0; i < a.size; i++)
    {
        printf("Please write the %d number you wish to push to the stack: ",
               i + 1);
        scanf("%d", &a.data[i]);
        push(s, &array[i]);
    }

    stacksize = get_size(s);

    stackarray = malloc(stacksize * sizeof(int));

    stack_to_array(s, stackarray);

    for (i = 0; i < stacksize; i++)
        printf("%d\n", stackarray[i]);

    free(stackarray);

    kill(s);

    return 0;
}
