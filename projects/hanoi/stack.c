#include "stack.h"
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct stack
{
    struct node *head;
    size_t size;
};

Stack *init(void)
{
    Stack *s;

    s = malloc(sizeof(struct stack));

    if (!s)
        return NULL;

    s->head = NULL;
    s->size = 0;

    return s;
}

int kill(Stack *s)
{
    struct node *current;
    struct node *temp;

    if (!s)
        return 1;

    current = s->head;

    while (current)
    {
        temp = current->next;
        free(current);
        current = temp;
        s->size--;
    }

    free(s);

    return 0;
}

size_t get_size(const Stack *s)
{
    if (!s)
        return 0;

    return s->size;
}

int push(Stack *s, int *input)
{
    struct node *newhead;

    if (!s || !input)
        return 1;

    newhead = malloc(sizeof(struct node));
    if (!newhead)
        return 2;

    newhead->data = *input;
    newhead->next = s->head;

    s->head = newhead;
    s->size++;

    return 0;
}

int pop(Stack *s, int *output)
{
    struct node *oldhead;

    if (!s || !output)
        return 1;

    if (!s->head)
        return 2;

    oldhead = s->head;
    *output = oldhead->data;

    s->head = oldhead->next;
    s->size--;

    free(oldhead);

    return 0;
}

int stack_to_array(const Stack *s, int *array)
{
    int i;
    struct node *current;

    i = 0;

    if (!s || !array)
        return 1;

    if (!s->head)
        return 2;

    current = s->head;

    while (current && i < s->size)
    {
        array[i] = current->data;
        current = current->next;
        i++;
    }

    return 0;
}
