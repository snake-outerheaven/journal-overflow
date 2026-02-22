#include "stack.h"
#include <stddef.h>
#include <stdio.h>
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

Stack *stack_init(void)
{
    Stack *s;

    s = malloc(sizeof(struct stack));

    if (!s)
        return NULL;

    s->head = NULL;
    s->size = 0;

    return s;
}

int stack_kill(Stack **s)
{
    struct node *current;
    struct node *temp;

    if (!s)
        return 1;

    if (!*s)
        return 2;

    current = (*s)->head;

    while (current)
    {
        temp = current->next;
        free(current);
        current = temp;
        (*s)->size--;
    }

    free(*s);
    *s = NULL;

    return 0;
}

size_t get_size(const Stack *s)
{
    if (!s)
        return 0;

    return s->size;
}

int peek(const Stack *s, int *output)
{
    if (!s || !output)
        return 1;

    if (!s->size)
        return 2;

    *output = s->head->data;

    return 0;
}

int peek_depth(const Stack *s, size_t depth, int *output)
{
    size_t i = 0;
    struct node *current = NULL;

    if (!s || !s->head || depth > s->size || !output)
        return 1;

    current = s->head;

    while (i < depth)
    {
        current = current->next;
        i++;
    }

    *output = current->data;

    return 0;
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

int stack_print(const Stack *s)
{
    int i = 0;
    struct node *current;

    if (!s)
        return 1;

    if (!s->head)
        return 2;

    current = s->head;

    while (current)
    {
        printf("Value: %d\tIndex: %d\n", current->data, i + 1);
        i++;
        current = current->next;
    }

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

int stack_invert(Stack *s)
{
    struct node *current = NULL;
    struct node *prev = NULL;
    struct node *next = NULL;

    if (!s)
        return 1;

    if (!s->head)
        return 2;

    current = s->head;

    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    s->head = prev;

    return 0;
}
