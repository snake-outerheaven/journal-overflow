#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

struct node
{
        struct node *prev;
        void *data;
        struct node *next;
};

int main()
{
        Node *p, *n;

        n = malloc(sizeof(Node));
        p = malloc(sizeof(Node));

        n->prev = NULL;
        n->data = malloc(1024);
        n->next = p;

        p->prev = n;
        p->data = malloc(1024);
        p->next = NULL;

        printf("Where main func is on memory: %p.\n", (void *)&main);
        printf("Where n and p are on on memory: %p\t%p.\n", (void *)n, (void *)p);
        printf("Where n data is on memory: %p.\n", (void *)n->data);
        printf("Where it points: %p.\n", (void *)n->next);
        printf("Where p data is on memory: %p.\n", (void *)p->data);
        printf("Where it points: %p.\n", (void *)p->prev);
        printf("Where n->prev points: %p.\n", (void *)n->prev);
        printf("Where p->next points: %p.\n", (void *)p->next);

        free(n->data);
        free(p->data);
        free(p);
        free(n);

        n->data = NULL;
        p->data = NULL;
        p = NULL;
        n = NULL;

        return 0;
}