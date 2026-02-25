#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
    Redoing exercise 3 of eloquent javascript in C
*/

#define MAX 10

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

Node *list_init();
int list_append(Node **, int);
void list_free(Node **);
void list_print(const Node *);

int main()
{
    size_t i;

    Node *n;

    n = list_init();

    for (i = 1; i < MAX; i++)
	    if(list_append(&n, (int)i))
			    puts("Erro ao adicionar número!");


    list_print(n);

    list_free(&n);

    putchar('\n');

    puts("It just works.");

    return 0;
}

Node *list_init()
{
	return NULL;
}

int list_append(Node **head, int value)
{
    Node *current;
    Node *new;

    if (!head)
        return 1;

    current = *head;
    new = malloc(sizeof(Node));

    if (!new)
        return 2;

    new->value = value;
    new->next = NULL;

    if(!*head)
    {
	    *head = new;
	    return 0;
    }


    while (current->next)
    {
        current = current->next;
    }

    new->value = value;
    new->next = NULL;

    current->next = new;

    return 0;
}

void list_free(Node **head)
{
    Node *temp;
    Node *current;

    if (!head)
        return;

    if (!*head)
        return;

    current = *head;

    while (current)
    {
        temp = current->next;
        free(current);
        current = temp;
    }

    *head = NULL;
}

void list_print(const Node *head)
{
    const Node *current;

    current = head;

    while (current->next)
    {
        printf("\t|%d|\t", current->value);
        current = current->next;
    }
}
