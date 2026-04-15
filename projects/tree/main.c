#include "tree.h"

#include <stdio.h>

int main()
{
    tree_t *tree = NULL;

    /* Nivel 1 - Raiz */
    tree = stree(tree, 'P');

    /* Nivel 2 */
    tree = stree(tree, 'H');
    tree = stree(tree, 'X');

    /* Nivel 3 */
    tree = stree(tree, 'D');
    tree = stree(tree, 'L');
    tree = stree(tree, 'T');
    tree = stree(tree, 'b');

    /* Nivel 4 */
    tree = stree(tree, 'B');
    tree = stree(tree, 'F');
    tree = stree(tree, 'J');
    tree = stree(tree, 'N');
    tree = stree(tree, 'R');
    tree = stree(tree, 'V');
    tree = stree(tree, 'Z');
    tree = stree(tree, 'd');

    /* Nivel 5 - Folhas */
    tree = stree(tree, 'A');
    tree = stree(tree, 'C');
    tree = stree(tree, 'E');
    tree = stree(tree, 'G');
    tree = stree(tree, 'I');
    tree = stree(tree, 'K');
    tree = stree(tree, 'M');
    tree = stree(tree, 'O');
    tree = stree(tree, 'Q');
    tree = stree(tree, 'S');
    tree = stree(tree, 'U');
    tree = stree(tree, 'W');
    tree = stree(tree, 'Y');
    tree = stree(tree, '[');
    tree = stree(tree, 'a');
    tree = stree(tree, 'c');
    tree = stree(tree, 'e');

    inorder(tree);

    ktree(tree);

    return 0;
}