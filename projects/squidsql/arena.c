/**
 * @file arena.c
 * @brief Implementation of the in-file allocator declared in arena.h.
 */
#include "arena.h"

#include <stdio.h>
#include <string.h>

/** File format version written to new files. */
#define ARENA_VERSION 1u
/** Bytes in front of every payload. */
#define BLOCK_HDR 16u
/** Tag of a block handed out by arena_alloc(). */
#define TAG_USED 0xA110C8EDu
/** Tag of a block sitting on a free list. */
#define TAG_FREE 0xF4EEB10Cu
/** Requests above this are refused outright (a sanity limit, 1 TiB). */
#define ALLOC_LIMIT (1ull << 40)

/** The 16 bytes that precede every payload. */
typedef struct
{
    uint64_t size; /**< Payload size, a multiple of 16. */
    uint64_t tag;  /**< ::TAG_USED or ::TAG_FREE. */
} block_hdr;

_Static_assert(sizeof(block_hdr) == BLOCK_HDR, "block header must be 16 bytes");

/**
 * @brief Gets the header of the block whose payload is at @p off.
 * @param a   Arena.
 * @param off Payload offset.
 * @return Pointer to the block header.
 */
static block_hdr *block_of(const arena *a, uint64_t off)
{
    return (block_hdr *)arena_ptr(a, off - BLOCK_HDR);
}

/**
 * @brief Rounds a size up to the allocation granularity (16 bytes, minimum 16).
 * @param n Requested size.
 * @return Rounded size.
 */
static uint64_t round_size(uint64_t n)
{
    if (n < 16)
    {
        n = 16;
    }
    return (n + 15u) & ~(uint64_t)15u;
}

/**
 * @brief Grows the file so that it holds at least @p end bytes.
 *
 * The size at least doubles each time, so growth is amortized.
 *
 * @param a   Arena.
 * @param end Required file size.
 * @return 0 on success, -1 on failure.
 */
static int ensure_size(arena *a, uint64_t end)
{
    char err[HAL_ERR_MAX];
    uint64_t size = a->map.size;

    if (end <= size)
    {
        return 0;
    }
    while (size < end)
    {
        size *= 2;
    }
    if (hal_grow(&a->map, size, err))
    {
        return -1;
    }
    arena_hdr(a)->file_size = a->map.size;
    return 0;
}

int arena_open(arena *a, const char *path, char *err)
{
    bool created;
    arena_header *h;

    memset(a, 0, sizeof *a);
    if (hal_open(&a->map, path, ARENA_INITIAL_SIZE, &created, err))
    {
        return -1;
    }
    h = arena_hdr(a);

    if (created)
    {
        memset(h, 0, sizeof *h);
        memcpy(h->magic, "SQUIDDB", 8);
        h->version = ARENA_VERSION;
        h->file_size = a->map.size;
        h->top = round_size(sizeof *h);
    }
    else
    {
        if (a->map.size < sizeof *h || memcmp(h->magic, "SQUIDDB", 8) != 0)
        {
            snprintf(err, HAL_ERR_MAX, "not a squidsql database file");
        }
        else if (h->version != ARENA_VERSION)
        {
            snprintf(err, HAL_ERR_MAX, "unsupported database version %u", (unsigned)h->version);
        }
        else if (h->file_size != a->map.size || h->top > a->map.size)
        {
            snprintf(err, HAL_ERR_MAX, "database file is truncated or damaged");
        }
        else
        {
            err[0] = '\0';
        }
        if (err[0])
        {
            hal_close(&a->map);
            return -1;
        }
        a->unclean = !h->clean;
    }

    h->clean = 0; /* stays 0 until arena_close() */
    if (hal_sync(&a->map, err))
    {
        hal_close(&a->map);
        return -1;
    }
    return 0;
}

void arena_close(arena *a)
{
    char err[HAL_ERR_MAX];

    if (!a->map.base)
    {
        return;
    }
    arena_hdr(a)->clean = 1;
    hal_sync(&a->map, err);
    hal_close(&a->map);
}

int arena_sync(arena *a, char *err)
{
    return hal_sync(&a->map, err);
}

uint64_t arena_alloc(arena *a, size_t request)
{
    uint64_t size, off, need;
    arena_header *h;

    if (request > ALLOC_LIMIT)
    {
        return 0;
    }
    size = round_size(request);
    h = arena_hdr(a);

    if (size <= ARENA_SMALL_MAX)
    {
        uint64_t *head = &h->small_free[size / 16 - 1];

        if (*head)
        {
            off = *head;
            *head = *(uint64_t *)arena_ptr(a, off);
            block_of(a, off)->tag = TAG_USED;
            memset(arena_ptr(a, off), 0, (size_t)size);
            return off;
        }
    }
    else
    {
        uint64_t *link = &h->large_free;

        while (*link)
        {
            off = *link;
            if (block_of(a, off)->size >= size)
            {
                *link = *(uint64_t *)arena_ptr(a, off);
                block_of(a, off)->tag = TAG_USED;
                memset(arena_ptr(a, off), 0, (size_t)block_of(a, off)->size);
                return off;
            }
            link = (uint64_t *)arena_ptr(a, off);
        }
    }

    need = BLOCK_HDR + size;
    if (ensure_size(a, h->top + need))
    {
        return 0;
    }
    h = arena_hdr(a); /* the file may have been remapped */
    off = h->top + BLOCK_HDR;
    block_of(a, off)->size = size;
    block_of(a, off)->tag = TAG_USED;
    h->top += need;
    return off; /* fresh file bytes are zero, and bump space was never used */
}

void arena_free(arena *a, uint64_t off)
{
    block_hdr *b;
    arena_header *h;
    uint64_t *head;

    if (off == 0)
    {
        return;
    }
    b = block_of(a, off);
    if (b->tag != TAG_USED)
    {
        return;
    }
    h = arena_hdr(a);
    head = b->size <= ARENA_SMALL_MAX ? &h->small_free[b->size / 16 - 1] : &h->large_free;

    b->tag = TAG_FREE;
    *(uint64_t *)arena_ptr(a, off) = *head;
    *head = off;
}

uint64_t arena_block_size(const arena *a, uint64_t off)
{
    return block_of(a, off)->size;
}
