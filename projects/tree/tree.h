#ifndef TREE_H
#define TREE_H

typedef struct tree_t tree_t;

tree_t *stree(tree_t *, char);

void inorder(tree_t *);

void ktree(tree_t *);

#endif