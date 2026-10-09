/**
 * @file rbtree.c
 * @brief Implementation of the offset-linked red-black tree (see rbtree.h).
 *
 * Children are kept in `child[2]` (0 = left, 1 = right) so the mirror-image
 * cases of insertion and deletion share one piece of code, parameterized by a
 * direction `d`. The algorithm is the one from CLRS; deletion relinks nodes
 * instead of copying keys, so offsets of surviving nodes never change.
 */
#include "rbtree.h"

#include <stddef.h>

/** Colour value of a red node. */
#define RED 0u
/** Colour value of a black node (and of the null link). */
#define BLACK 1u

/** A tree node as stored in the arena (48 bytes). */
typedef struct
{
    uint64_t child[2]; /**< Left and right child offsets, 0 if none. */
    uint64_t parent;   /**< Parent offset, 0 for the root. */
    uint64_t key;      /**< Node key word, interpreted by the callback. */
    uint64_t val;      /**< Value word. */
    uint64_t color;    /**< ::RED or ::BLACK. */
} rb_node;

/**
 * @brief Resolves a node offset to a pointer.
 * @param t   Tree.
 * @param off Node offset; 0 yields NULL.
 * @return Pointer valid until the next arena allocation, or NULL.
 */
static rb_node *N(const rb_tree *t, uint64_t off)
{
    return off ? (rb_node *)arena_ptr(t->a, off) : NULL;
}

/**
 * @brief Reads the root offset.
 * @param t Tree.
 * @return Offset of the root, 0 if empty.
 */
static uint64_t get_root(const rb_tree *t)
{
    return *(uint64_t *)arena_ptr(t->a, t->root_ref);
}

/**
 * @brief Writes the root offset.
 * @param t    Tree.
 * @param root New root offset.
 */
static void set_root(const rb_tree *t, uint64_t root)
{
    *(uint64_t *)arena_ptr(t->a, t->root_ref) = root;
}

/**
 * @brief Colour of a node; the null link counts as black.
 * @param t   Tree.
 * @param off Node offset or 0.
 * @return ::RED or ::BLACK.
 */
static uint64_t color_of(const rb_tree *t, uint64_t off)
{
    return off ? N(t, off)->color : BLACK;
}

/**
 * @brief Makes @p v take the place of @p u under u's parent.
 *
 * Only the parent's link and v's parent pointer change; u keeps its own links.
 *
 * @param t Tree.
 * @param u Node being replaced.
 * @param v Replacement, may be 0.
 */
static void replace_child(const rb_tree *t, uint64_t u, uint64_t v)
{
    uint64_t p = N(t, u)->parent;

    if (!p)
    {
        set_root(t, v);
    }
    else if (N(t, p)->child[0] == u)
    {
        N(t, p)->child[0] = v;
    }
    else
    {
        N(t, p)->child[1] = v;
    }
    if (v)
    {
        N(t, v)->parent = p;
    }
}

/**
 * @brief Rotates the subtree at @p x downward in direction @p d.
 *
 * `d == 0` is a left rotation (x's right child becomes the subtree root);
 * `d == 1` is a right rotation.
 *
 * @param t Tree.
 * @param x Node to rotate down; its child on side `!d` must exist.
 * @param d Direction, 0 or 1.
 */
static void rotate(const rb_tree *t, uint64_t x, int d)
{
    uint64_t y = N(t, x)->child[!d];
    uint64_t inner = N(t, y)->child[d];

    N(t, x)->child[!d] = inner;
    if (inner)
    {
        N(t, inner)->parent = x;
    }
    replace_child(t, x, y); /* y.parent = x.parent, parent's link -> y */
    N(t, y)->child[d] = x;
    N(t, x)->parent = y;
}

void rb_init(rb_tree *t, arena *a, uint64_t root_ref, rb_cmp cmp)
{
    t->a = a;
    t->root_ref = root_ref;
    t->cmp = cmp;
}

uint64_t rb_find(const rb_tree *t, const void *key)
{
    uint64_t cur = get_root(t);

    while (cur)
    {
        int c = t->cmp(t->a, N(t, cur)->key, key);

        if (c == 0)
        {
            return cur;
        }
        cur = N(t, cur)->child[c < 0]; /* node < key: go right */
    }
    return 0;
}

/**
 * @brief Restores the invariants after inserting the red node @p z.
 * @param t Tree.
 * @param z Newly inserted red node.
 */
static void insert_fixup(const rb_tree *t, uint64_t z)
{
    while (N(t, z)->parent && color_of(t, N(t, z)->parent) == RED)
    {
        uint64_t p = N(t, z)->parent;
        uint64_t g = N(t, p)->parent; /* a red parent is never the root */
        int d = N(t, g)->child[0] == p ? 0 : 1;
        uint64_t u = N(t, g)->child[!d];

        if (color_of(t, u) == RED)
        {
            N(t, p)->color = BLACK;
            N(t, u)->color = BLACK;
            N(t, g)->color = RED;
            z = g;
        }
        else
        {
            if (z == N(t, p)->child[!d])
            {
                z = p;
                rotate(t, z, d);
                p = N(t, z)->parent;
            }
            N(t, p)->color = BLACK;
            N(t, g)->color = RED;
            rotate(t, g, !d);
        }
    }
    N(t, get_root(t))->color = BLACK;
}

rb_status rb_insert(rb_tree *t, const void *key, uint64_t node_key, uint64_t val)
{
    uint64_t parent = 0, cur = get_root(t), z;
    int side = 0;
    rb_node *n;

    while (cur)
    {
        int c = t->cmp(t->a, N(t, cur)->key, key);

        if (c == 0)
        {
            return RB_DUP;
        }
        parent = cur;
        side = c < 0; /* node < key: go right */
        cur = N(t, cur)->child[side];
    }

    z = arena_alloc(t->a, sizeof(rb_node)); /* may remap: only offsets are held */
    if (!z)
    {
        return RB_NOMEM;
    }
    n = N(t, z);
    n->key = node_key;
    n->val = val;
    n->parent = parent;
    n->color = RED;

    if (!parent)
    {
        set_root(t, z);
    }
    else
    {
        N(t, parent)->child[side] = z;
    }
    insert_fixup(t, z);
    return RB_OK;
}

/**
 * @brief Finds the leftmost node of a subtree.
 * @param t Tree.
 * @param n Subtree root, non-zero.
 * @return Offset of the node with the smallest key in the subtree.
 */
static uint64_t minimum(const rb_tree *t, uint64_t n)
{
    while (N(t, n)->child[0])
    {
        n = N(t, n)->child[0];
    }
    return n;
}

/**
 * @brief Restores the invariants after removing a black node.
 *
 * @p x carries an "extra black". It may be 0 (a null link), so its parent is
 * passed separately.
 *
 * @param t  Tree.
 * @param x  Node that took the removed node's place, or 0.
 * @param xp Parent of @p x.
 */
static void delete_fixup(const rb_tree *t, uint64_t x, uint64_t xp)
{
    while (x != get_root(t) && color_of(t, x) == BLACK)
    {
        int d = N(t, xp)->child[0] == x ? 0 : 1; /* x is child d of xp */
        uint64_t w = N(t, xp)->child[!d];        /* sibling: exists, x is double black */

        if (color_of(t, w) == RED)
        {
            N(t, w)->color = BLACK;
            N(t, xp)->color = RED;
            rotate(t, xp, d);
            w = N(t, xp)->child[!d];
        }
        if (color_of(t, N(t, w)->child[0]) == BLACK && color_of(t, N(t, w)->child[1]) == BLACK)
        {
            N(t, w)->color = RED;
            x = xp;
            xp = N(t, x)->parent;
        }
        else
        {
            if (color_of(t, N(t, w)->child[!d]) == BLACK)
            {
                N(t, N(t, w)->child[d])->color = BLACK;
                N(t, w)->color = RED;
                rotate(t, w, !d);
                w = N(t, xp)->child[!d];
            }
            N(t, w)->color = N(t, xp)->color;
            N(t, xp)->color = BLACK;
            N(t, N(t, w)->child[!d])->color = BLACK;
            rotate(t, xp, d);
            x = get_root(t);
            break;
        }
    }
    if (x)
    {
        N(t, x)->color = BLACK;
    }
}

void rb_delete(rb_tree *t, uint64_t z)
{
    uint64_t y = z, x, xp;
    uint64_t y_color = N(t, y)->color;

    if (!N(t, z)->child[0])
    {
        x = N(t, z)->child[1];
        xp = N(t, z)->parent;
        replace_child(t, z, x);
    }
    else if (!N(t, z)->child[1])
    {
        x = N(t, z)->child[0];
        xp = N(t, z)->parent;
        replace_child(t, z, x);
    }
    else
    {
        y = minimum(t, N(t, z)->child[1]);
        y_color = N(t, y)->color;
        x = N(t, y)->child[1];
        if (N(t, y)->parent == z)
        {
            xp = y;
        }
        else
        {
            xp = N(t, y)->parent;
            replace_child(t, y, x);
            N(t, y)->child[1] = N(t, z)->child[1];
            N(t, N(t, y)->child[1])->parent = y;
        }
        replace_child(t, z, y);
        N(t, y)->child[0] = N(t, z)->child[0];
        N(t, N(t, y)->child[0])->parent = y;
        N(t, y)->color = N(t, z)->color;
    }

    if (y_color == BLACK)
    {
        delete_fixup(t, x, xp);
    }
    arena_free(t->a, z);
}

uint64_t rb_first(const rb_tree *t)
{
    uint64_t root = get_root(t);

    return root ? minimum(t, root) : 0;
}

uint64_t rb_next(const rb_tree *t, uint64_t n)
{
    uint64_t p;

    if (N(t, n)->child[1])
    {
        return minimum(t, N(t, n)->child[1]);
    }
    p = N(t, n)->parent;
    while (p && n == N(t, p)->child[1])
    {
        n = p;
        p = N(t, p)->parent;
    }
    return p;
}

uint64_t rb_key(const rb_tree *t, uint64_t node)
{
    return N(t, node)->key;
}

uint64_t rb_val(const rb_tree *t, uint64_t node)
{
    return N(t, node)->val;
}

/**
 * @brief Validates the subtree at @p n and returns its black height.
 * @param t     Tree.
 * @param n     Subtree root or 0.
 * @param count Incremented once per node visited.
 * @return Black height (counting the null link as 1), or -1 if invalid.
 */
static int check_node(const rb_tree *t, uint64_t n, uint64_t *count)
{
    int side, h[2];

    if (!n)
    {
        return 1;
    }
    (*count)++;
    for (side = 0; side < 2; side++)
    {
        uint64_t c = N(t, n)->child[side];

        if (c && N(t, c)->parent != n)
        {
            return -1;
        }
        if (c && N(t, n)->color == RED && N(t, c)->color == RED)
        {
            return -1;
        }
        h[side] = check_node(t, c, count);
        if (h[side] < 0)
        {
            return -1;
        }
    }
    if (h[0] != h[1])
    {
        return -1;
    }
    return h[0] + (N(t, n)->color == BLACK ? 1 : 0);
}

int rb_check(const rb_tree *t, uint64_t *count)
{
    uint64_t root = get_root(t), n = 0;
    int rc;

    if (root && (N(t, root)->color != BLACK || N(t, root)->parent != 0))
    {
        return -1;
    }
    rc = check_node(t, root, &n);
    if (count)
    {
        *count = n;
    }
    return rc < 0 ? -1 : 0;
}
