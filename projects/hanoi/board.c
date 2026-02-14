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

Board *board_init(int discs)
{
    Board *b;

    b = malloc(sizeof(struct board));

    if (!b)
        return NULL;

    if (!(b->left = stack_init()) || !(b->middle = stack_init()) || !(b->right = stack_init()))
    {
        if (b->left)
            stack_kill(&b->left);

        if (b->middle)
            stack_kill(&b->middle);

        if (b->right)
            stack_kill(&b->right);

        free(b);

        return NULL;
    }

    return b;
}

int board_kill(Board *b)
{
    if (!b)
        return ARG_ERROR;

    if (!b->left || !b->middle || !b->right)
    {
        if (b->left)
            stack_kill(&b->left);

        if (b->middle)
            stack_kill(&b->middle);

        if (b->right)
            stack_kill(&b->right);

        free(b);

        return MALLOC_ERROR;
    }

    stack_kill(&b->left);
    stack_kill(&b->middle);
    stack_kill(&b->right);

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
