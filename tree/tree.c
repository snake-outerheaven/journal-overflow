
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

struct tree_t
{
    char info;
    struct tree_t *left;
    struct tree_t *right;
};

tree_t *stree(tree_t *r, char info)
{
    if (!r)
    {
        r = (tree_t *)malloc(sizeof(tree_t));
        if (!r)
        {
            printf("\nSem memória!");
            exit(1);
        }
        r->left = NULL;
        r->right = NULL;
        r->info = info;
        return r;
    }

    if (info < r->info)
        r->left = stree(r->left, info);
    else if (info > r->info)
        r->right = stree(r->right, info);

    return r;
}
static void run_lateral(tree_t *r, int level)
{
    int i;
    if (!r)
    {
        return;
    }

    /* 1. Primeiro a Direita: os maiores valores ficam no topo do terminal */
    run_lateral(r->right, level + 1);

    /* 2. Impressao do No com indentacao proporcional ao nivel */
    for (i = 0; i < level; i++)
    {
        printf("        "); /* 8 espacos para dar amplitude visual */
    }

    if (level > 0)
    {
        printf("|-------"); /* "Galho" para conectar visualmente */
    }

    printf("[%c]\n", r->info);

    /* 3. Por ultimo a Esquerda: os menores valores ficam na base do terminal */
    run_lateral(r->left, level + 1);
}

void inorder(tree_t *root)
{
    if (!root)
    {
        printf("Arvore vazia.\n");
        return;
    }
    run_lateral(root, 0);
}

void ktree(tree_t *root)
{
    if (!root)
        return;

    ktree(root->left);
    ktree(root->right);

    free(root);
}