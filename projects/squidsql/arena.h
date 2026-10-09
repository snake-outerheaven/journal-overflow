/**
 * @file arena.h
 * @brief A memory allocator that lives inside the mapped database file.
 *
 * Everything the database stores is allocated here and referred to by its
 * **offset** from the start of the file (an `uint64_t`), never by pointer:
 * the file can be remapped at a different address whenever it grows.
 * Offset 0 is the file header, so it doubles as the "null" offset.
 *
 * ### File layout
 *
 *     offset 0            ::arena_header
 *     arena_header.top    first never-used byte; blocks are carved from here
 *     ...                 blocks: [ 16-byte block header | payload ]
 *
 * ### Allocation strategy
 *
 * Sizes are rounded up to a multiple of 16 bytes. Freed blocks go on a free
 * list: one list per size up to ::ARENA_SMALL_MAX bytes, plus a single
 * first-fit list for larger blocks. Free blocks are not coalesced.
 *
 * ### Pointer rule
 *
 * arena_alloc() may grow the file, which invalidates every pointer obtained
 * from arena_ptr(). Keep offsets across allocations and call arena_ptr() again
 * afterwards.
 *
 * ### Durability
 *
 * The file is not crash-safe. The header records whether the file was closed
 * cleanly; after a crash arena_open() reports it through arena::unclean but
 * does not repair anything.
 */
#ifndef ARENA_H
#define ARENA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "hal.h"

/** Number of exact-size free lists (sizes 16, 32, ... ::ARENA_SMALL_MAX). */
#define ARENA_NCLASSES 64
/** Largest block size served by an exact-size free list, in bytes. */
#define ARENA_SMALL_MAX (ARENA_NCLASSES * 16)
/** Size of a new database file, in bytes. */
#define ARENA_INITIAL_SIZE (64u * 1024u)

/** The first bytes of the file. Fields are stored in host byte order. */
typedef struct
{
    char magic[8];                       /**< `"SQUIDDB"` plus NUL; identifies the file. */
    uint32_t version;                    /**< File format version. */
    uint32_t clean;                      /**< 1 if the file was closed cleanly, 0 while open. */
    uint64_t file_size;                  /**< Size the file had after the last growth. */
    uint64_t top;                        /**< Offset of the first byte never handed out. */
    uint64_t small_free[ARENA_NCLASSES]; /**< Heads of the exact-size free lists. */
    uint64_t large_free;                 /**< Head of the free list for blocks above ::ARENA_SMALL_MAX. */
    uint64_t catalog_root;               /**< Root of the table catalog tree (see db.c). */
} arena_header;

/** An open database file. */
typedef struct
{
    hal_map map;  /**< The mapped file. */
    bool unclean; /**< True if the file was not closed cleanly last time. */
} arena;

/**
 * @brief Opens a database file, creating and formatting it if it is new.
 * @param a    Arena to fill.
 * @param path Path of the database file.
 * @param err  Buffer of ::HAL_ERR_MAX bytes; receives a message on failure.
 * @return 0 on success, -1 on failure (not a squidsql file, wrong version,
 *         truncated, in use by another process, or an OS error).
 */
int arena_open(arena *a, const char *path, char *err);

/**
 * @brief Marks the file as cleanly closed, flushes it and closes it.
 * @param a Arena to close.
 */
void arena_close(arena *a);

/**
 * @brief Flushes all changes to disk.
 * @param a   Arena to flush.
 * @param err Buffer of ::HAL_ERR_MAX bytes; receives a message on failure.
 * @return 0 on success, -1 on failure.
 */
int arena_sync(arena *a, char *err);

/**
 * @brief Allocates a zero-filled block of at least @p size bytes.
 *
 * May grow (and remap) the file; see the pointer rule in the file comment.
 *
 * @param a    Arena.
 * @param size Requested payload size in bytes.
 * @return Offset of the payload (always a multiple of 16 and never 0), or 0 if
 *         the file could not grow.
 */
uint64_t arena_alloc(arena *a, size_t size);

/**
 * @brief Returns a block to its free list.
 *
 * Offset 0 is ignored. A block that is not currently allocated (for example a
 * double free) is ignored too.
 *
 * @param a   Arena.
 * @param off Offset returned by arena_alloc().
 */
void arena_free(arena *a, uint64_t off);

/**
 * @brief Returns the usable size of an allocated block.
 * @param a   Arena.
 * @param off Offset returned by arena_alloc().
 * @return Payload size in bytes, which may exceed the requested size.
 */
uint64_t arena_block_size(const arena *a, uint64_t off);

/**
 * @brief Returns the file header.
 * @param a Arena.
 * @return Pointer to the header; valid until the next arena_alloc().
 */
static inline arena_header *arena_hdr(const arena *a)
{
    return (arena_header *)a->map.base;
}

/**
 * @brief Converts an offset to a pointer.
 * @param a   Arena.
 * @param off Offset of a block (or of anything inside the file).
 * @return Pointer to that byte; valid until the next arena_alloc().
 */
static inline void *arena_ptr(const arena *a, uint64_t off)
{
    return (unsigned char *)a->map.base + off;
}

#endif
