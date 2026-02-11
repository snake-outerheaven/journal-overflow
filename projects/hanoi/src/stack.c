#include "../include/stack.h"
#include <stddef.h>
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

int push(Stack *s, int *input)
{
    struct node *newhead;

    if (!s || !input)
        return EXIT_FAILURE;

    newhead = malloc(sizeof(struct node));
    if (!newhead)
        return EXIT_FAILURE;

    newhead->data = *input;
    newhead->next = s->head;

    s->head = newhead;
    s->size++;

    return EXIT_SUCCESS;
}

int pop(Stack *s, int *output)
{
    struct node *oldhead;

    if (!s || !output)
        return EXIT_FAILURE;

    if (!s->head)
        return EXIT_FAILURE;

    oldhead = s->head;
    *output = oldhead->data;

    s->head = oldhead->next;
    s->size--;

    free(oldhead);

    return EXIT_SUCCESS;
}
