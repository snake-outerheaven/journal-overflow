/**
 * @file test_storage.c
 * @brief Tests for the storage layer: HAL, arena and red-black tree.
 *
 * Exits with status 0 and prints "storage tests passed" if every check holds;
 * otherwise prints the failing condition and exits with status 1.
 * Usage: `test_storage [scratch-file]` (default `test_storage.db`, deleted at the end).
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../arena.h"
#include "../rbtree.h"

/** Fails the whole test run, printing the condition, if @p c is false. */
#define CHECK(c)                                                     \
    do                                                               \
    {                                                                \
        if (!(c))                                                    \
        {                                                            \
            printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #c);      \
            exit(1);                                                 \
        }                                                            \
    } while (0)

/** Path of the scratch database. */
static const char *path = "test_storage.db";
/** State of the pseudo-random generator (xorshift64). */
static uint64_t rng_state = 88172645463325252ull;

/**
 * @brief Returns the next pseudo-random number (deterministic, so failures reproduce).
 * @return A 64-bit value.
 */
static uint64_t rnd(void)
{
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 7;
    rng_state ^= rng_state << 17;
    return rng_state;
}

/**
 * @brief Key comparison for trees keyed by an integer.
 * @param a        Arena (unused).
 * @param node_key Stored key.
 * @param key      `const uint64_t *` searched key.
 * @return Negative, zero or positive.
 */
static int u64_cmp(const arena *a, uint64_t node_key, const void *key)
{
    uint64_t k = *(const uint64_t *)key;

    (void)a;
    return (node_key > k) - (node_key < k);
}

/**
 * @brief Opens the scratch database, failing the test on error.
 * @param a Arena to fill.
 */
static void open_arena(arena *a)
{
    char err[HAL_ERR_MAX];

    if (arena_open(a, path, err))
    {
        printf("FAIL arena_open: %s\n", err);
        exit(1);
    }
}

/**
 * @brief Allocator: allocation, reuse, growth beyond the initial size, reopen.
 */
static void test_arena(void)
{
    enum { N = 100 };
    uint64_t off[N], big, again;
    size_t size[N];
    arena a;
    int i;
    unsigned char *p;

    remove(path);
    open_arena(&a);
    CHECK(!a.unclean);

    for (i = 0; i < N; i++)
    {
        size[i] = (size_t)(1 + i * 3);
        off[i] = arena_alloc(&a, size[i]);
        CHECK(off[i] != 0 && off[i] % 16 == 0);
        CHECK(arena_block_size(&a, off[i]) >= size[i]);
        memset(arena_ptr(&a, off[i]), 0x40 + i % 32, size[i]);
    }

    big = arena_alloc(&a, 200 * 1024); /* larger than the whole initial file */
    CHECK(big != 0);
    CHECK(a.map.size > ARENA_INITIAL_SIZE);
    memset(arena_ptr(&a, big), 0x7E, 200 * 1024);

    for (i = 0; i < N; i++) /* offsets must survive the remap */
    {
        p = (unsigned char *)arena_ptr(&a, off[i]);
        CHECK(p[0] == 0x40 + i % 32 && p[size[i] - 1] == 0x40 + i % 32);
    }

    arena_free(&a, off[5]); /* small block: exact-size list, reused and zeroed */
    again = arena_alloc(&a, size[5]);
    CHECK(again == off[5]);
    CHECK(((unsigned char *)arena_ptr(&a, again))[0] == 0);

    arena_free(&a, big); /* large block: first-fit list */
    arena_free(&a, big); /* double free is ignored */
    again = arena_alloc(&a, 100 * 1024);
    CHECK(again == big);

    arena_hdr(&a)->catalog_root = 12345;
    arena_close(&a);

    open_arena(&a);
    CHECK(!a.unclean);
    CHECK(arena_hdr(&a)->catalog_root == 12345);
    p = (unsigned char *)arena_ptr(&a, off[7]);
    CHECK(p[0] == 0x40 + 7 % 32);

    hal_close(&a.map); /* simulate a crash: the clean flag is never set */
    open_arena(&a);
    CHECK(a.unclean);
    arena_close(&a);
    remove(path);
}

/**
 * @brief Builds a tree handle rooted in the file header.
 * @param t Handle to fill.
 * @param a Open arena.
 */
static void header_tree(rb_tree *t, arena *a)
{
    rb_init(t, a, offsetof(arena_header, catalog_root), u64_cmp);
}

/**
 * @brief Inserts an integer key.
 * @param t   Tree.
 * @param key Key; also stored as the value.
 * @return The rb_insert() status.
 */
static rb_status put(rb_tree *t, uint64_t key)
{
    return rb_insert(t, &key, key, key * 2);
}

/**
 * @brief Verifies that the tree holds exactly the keys marked in @p present.
 * @param t       Tree.
 * @param present One flag per key.
 * @param nkeys   Number of flags.
 */
static void check_contents(const rb_tree *t, const unsigned char *present, uint64_t nkeys)
{
    uint64_t k, n = rb_first(t), count = 0;

    for (k = 0; k < nkeys; k++)
    {
        if (!present[k])
        {
            continue;
        }
        CHECK(n != 0);
        CHECK(rb_key(t, n) == k && rb_val(t, n) == k * 2);
        n = rb_next(t, n);
        count++;
    }
    CHECK(n == 0);
    CHECK(rb_check(t, &k) == 0 && k == count);
}

/**
 * @brief Red-black tree: random inserts/deletes against a reference set,
 *        invariants, memory reuse and persistence.
 */
static void test_tree(void)
{
    enum { KEYS = 20000, OPS = 60000, FILL = 5000 };
    static unsigned char present[KEYS];
    uint64_t count = 0, i, top, n;
    arena a;
    rb_tree t;

    remove(path);
    open_arena(&a);
    header_tree(&t, &a);
    CHECK(rb_first(&t) == 0);
    CHECK(rb_check(&t, NULL) == 0);

    for (i = 0; i < OPS; i++)
    {
        uint64_t key = rnd() % KEYS;

        if (present[key] && rnd() % 2)
        {
            n = rb_find(&t, &key);
            CHECK(n != 0 && rb_key(&t, n) == key);
            rb_delete(&t, n);
            present[key] = 0;
            count--;
        }
        else if (present[key])
        {
            CHECK(put(&t, key) == RB_DUP);
        }
        else
        {
            CHECK(put(&t, key) == RB_OK);
            present[key] = 1;
            count++;
        }
        if (i % 1000 == 0)
        {
            uint64_t seen;

            CHECK(rb_check(&t, &seen) == 0 && seen == count);
        }
    }
    check_contents(&t, present, KEYS);

    /* deleting everything leaves an empty, valid tree and frees all nodes */
    top = arena_hdr(&a)->top;
    for (i = 0; (n = rb_first(&t)) != 0; i++)
    {
        present[rb_key(&t, n)] = 0;
        rb_delete(&t, n);
        if (i % 500 == 0)
        {
            CHECK(rb_check(&t, NULL) == 0);
        }
    }
    CHECK(rb_check(&t, &n) == 0 && n == 0);

    /* ascending inserts (the worst case for an unbalanced tree), reusing freed nodes */
    memset(present, 0, sizeof present);
    for (i = 0; i < FILL; i++)
    {
        CHECK(put(&t, i) == RB_OK);
        present[i] = 1;
    }
    CHECK(arena_hdr(&a)->top <= top); /* nodes came from the free list */
    check_contents(&t, present, KEYS);

    arena_close(&a);
    open_arena(&a);
    header_tree(&t, &a);
    check_contents(&t, present, KEYS);

    /* keep growing past the current file size */
    for (i = FILL; i < 200000; i++)
    {
        CHECK(put(&t, i) == RB_OK);
    }
    CHECK(rb_check(&t, &n) == 0 && n == 200000);
    CHECK(a.map.size > 8u * 1024u * 1024u);

    arena_close(&a);
    remove(path);
}

/**
 * @brief Runs every test.
 * @param argc Argument count.
 * @param argv Optional scratch file path.
 * @return 0 if all tests pass (a failed check exits with 1 on the spot).
 */
int main(int argc, char **argv)
{
    if (argc > 1)
    {
        path = argv[1];
    }
    test_arena();
    test_tree();
    printf("storage tests passed\n");
    return 0;
}
