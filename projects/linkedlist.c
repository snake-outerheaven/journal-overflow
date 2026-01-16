#include <stdio.h>
#include <stdlib.h>

/*
    Redoing exercise 3 of eloquent javascript in C
*/

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

Node *list_init();
int list_append(Node *, int);

int main()
{
    Node *n;
    n = list_init();
    if (list_append(n, 3))
        puts("Uuups!");
    puts("It just works.");
    return 0;
}

Node *list_init()
{
    Node *p;

    p = malloc(sizeof(Node));

    p->value = 0;
    p->next = NULL;

    return p;
}

int list_append(Node *head, int value)
{
    Node *current;
    Node *new;

    if (!head)
        return 1;

    current = head;
    new = malloc(sizeof(Node));

    if (!new)
        return 2;

    while (current->next != NULL)
    {
        current = current->next;
    }

    new->value = value;
    new->next = NULL;

    current->next = new;

    return 0;
}