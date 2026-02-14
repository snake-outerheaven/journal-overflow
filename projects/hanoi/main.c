#include "stack.h"
#include <stddef.h>
#include <stdio.h>

#define MAX 7

int main(void)
{
    int i;
    Stack *s = NULL;

    printf("Where does the stack pointer is pointing to right now: %p\n",
           (void *)s);

    s = stack_init();

    printf("Where does the stack pointer is pointing to right now: %p\n",
           (void *)s);

    for (i = 0; i <= MAX; i++)
        push(s, &i);

    stack_print(s);

    stack_kill(&s);

    printf("Where does the stack pointer is pointing to right now: %p\n",
           (void *)s);

    return 0;
}
