/**
 * @file rbtree.h
 * @brief A red-black tree whose nodes live in the arena and link by offset.
 *
 * Each node stores its children, parent, colour, a 64-bit @e key and a 64-bit
 * @e value. All links are arena offsets, so the tree survives the file being
 * remapped and reopened. Offset 0 is the null link.
 *
 * ### Keys
 *
 * The tree does not interpret keys itself. The user supplies a comparison
 * callback (::rb_cmp). The stored @e node key is a 64-bit word that the
 * callback understands: an integer for a row-id tree, or the offset of a
 * string for the table catalog. The @e search key given to rb_find() and
 * rb_insert() may be of another type (for example a `const char *`), which is
 * why the two are separate.
 *
 * ### Where the root lives
 *
 * The root is a 64-bit word stored in the arena, identified by its offset
 * (@e root_ref). It can sit in the file header or inside a table record, so
 * updating the root persists automatically.
 *
 * ### Pointer rule
 *
 * rb_insert() allocates, which can remap the file. The functions here only
 * keep offsets, but a callback must not cache pointers either.
 */
#ifndef RBTREE_H
#define RBTREE_H

#include <stdint.h>

#include "arena.h"

/**
 * @brief Compares a stored node key with a search key.
 * @param a        Arena, for keys that are offsets of data.
 * @param node_key The key stored in a node.
 * @param key      The search key passed to rb_find() / rb_insert().
 * @return Negative if the node's key sorts before @p key, positive if after,
 *         0 if they are equal.
 */
typedef int (*rb_cmp)(const arena *a, uint64_t node_key, const void *key);

/** A handle to a tree; cheap to build and pass around. */
typedef struct
{
    arena *a;           /**< Arena holding the nodes. */
    uint64_t root_ref;  /**< Offset of the 64-bit word that holds the root offset. */
    rb_cmp cmp;         /**< Key comparison. */
} rb_tree;

/** Result of rb_insert(). */
typedef enum
{
    RB_OK,    /**< Inserted. */
    RB_DUP,   /**< A node with an equal key already exists; nothing changed. */
    RB_NOMEM  /**< The arena could not grow; nothing changed. */
} rb_status;

/**
 * @brief Builds a tree handle.
 * @param t        Handle to fill.
 * @param a        Arena holding the tree.
 * @param root_ref Offset of the zero-initialized 64-bit root word.
 * @param cmp      Key comparison callback.
 */
void rb_init(rb_tree *t, arena *a, uint64_t root_ref, rb_cmp cmp);

/**
 * @brief Inserts a node.
 * @param t        Tree.
 * @param key      Search key, passed to the callback to find the position.
 * @param node_key Key word to store in the new node.
 * @param val      Value word to store (typically the offset of a record).
 * @return ::RB_OK, ::RB_DUP or ::RB_NOMEM.
 */
rb_status rb_insert(rb_tree *t, const void *key, uint64_t node_key, uint64_t val);

/**
 * @brief Finds the node whose key equals @p key.
 * @param t   Tree.
 * @param key Search key.
 * @return Offset of the node, or 0 if there is none.
 */
uint64_t rb_find(const rb_tree *t, const void *key);

/**
 * @brief Deletes a node and frees its memory.
 *
 * Other nodes keep their offsets, so a saved offset from rb_next() stays valid
 * across the deletion of the node before it.
 *
 * @param t    Tree.
 * @param node Offset of a node of this tree.
 */
void rb_delete(rb_tree *t, uint64_t node);

/**
 * @brief Returns the node with the smallest key.
 * @param t Tree.
 * @return Offset of the node, or 0 if the tree is empty.
 */
uint64_t rb_first(const rb_tree *t);

/**
 * @brief Returns the in-order successor of a node.
 * @param t    Tree.
 * @param node Offset of a node.
 * @return Offset of the next node by key order, or 0 if @p node is the last.
 */
uint64_t rb_next(const rb_tree *t, uint64_t node);

/**
 * @brief Reads the key word stored in a node.
 * @param t    Tree.
 * @param node Offset of a node.
 * @return The node key.
 */
uint64_t rb_key(const rb_tree *t, uint64_t node);

/**
 * @brief Reads the value word stored in a node.
 * @param t    Tree.
 * @param node Offset of a node.
 * @return The value.
 */
uint64_t rb_val(const rb_tree *t, uint64_t node);

/**
 * @brief Checks the red-black invariants; meant for tests.
 *
 * Verifies that the root is black, no red node has a red child, every path has
 * the same number of black nodes, and parent links match child links.
 *
 * @param t     Tree.
 * @param count If not NULL, receives the number of nodes.
 * @return 0 if the tree is valid, -1 otherwise.
 */
int rb_check(const rb_tree *t, uint64_t *count);

#endif
