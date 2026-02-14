#include "board.h"
#include "stack.h"
#include <stddef.h>
#include <stdlib.h>

#define ARG_ERROR 1
#define MALLOC_ERROR 2
#define SUCCESS 0

struct board
{
    Stack *left;
    Stack *middle;
    Stack *right;
};

Board *init_board(int discs)
{
    Board *b;

    b = malloc(sizeof(struct board));

    if (!b)
        return NULL;

    if (!(b->left = init()) || !(b->middle = init()) || !(b->right = init()))
    {
        if (b->left)
            kill(b->left);

        if (b->middle)
            kill(b->middle);

        if (b->right)
            kill(b->right);

        free(b);

        return NULL;
    }

    return b;
}

int kill_board(Board *b)
{
    if (!b)
        return ARG_ERROR;

    if (!b->left || !b->middle || !b->right)
    {
        if (b->left)
            kill(b->left);

        if (b->middle)
            kill(b->middle);

        if (b->right)
            kill(b->right);

        free(b);

        return MALLOC_ERROR;
    }

    kill(b->left);
    kill(b->middle);
    kill(b->right);

    free(b);

    return 0;
}

int move(Board *b, size_t src, size_t dest)
{
    int i, peeked, temp, compare1, compare2;
    Stack *stacks[3], *from, *to;

    if (!b || src > 2 || dest > 2)
        return ARG_ERROR;

    stacks[0] = b->left;
    stacks[1] = b->middle;
    stacks[2] = b->right;

    if (peek(stacks[src], &peeked))
        return ARG_ERROR;

    from = stacks[src];
    to = stacks[dest];

    if (!peek(from, &compare1))
    {
        if (!peek(to, &compare2))
            if (compare1 > compare2)
                return ARG_ERROR;
    }
    else
        return ARG_ERROR;

    pop(from, &temp);
    push(to, &temp);

    return SUCCESS;
}
