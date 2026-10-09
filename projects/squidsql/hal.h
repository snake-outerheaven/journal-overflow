/**
 * @file hal.h
 * @brief Hardware/OS abstraction layer: a file mapped into memory.
 *
 * The rest of squidsql sees the database as one contiguous block of bytes
 * (hal_map::base, hal_map::size) that is backed by a file. Two
 * implementations provide it:
 *
 * - `hal_win32.c`: CreateFileMapping / MapViewOfFile.
 * - `hal_posix.c`: mmap / ftruncate / msync.
 *
 * Growing the file remaps it, so **hal_map::base may change** after
 * hal_grow(). Code above this layer must refer to data by offset from the base
 * and never keep a raw pointer across a call that can grow the file.
 */
#ifndef HAL_H
#define HAL_H

#include <stdbool.h>
#include <stdint.h>

/** Size of the buffer that receives error messages. */
#define HAL_ERR_MAX 160

/** A file mapped into the address space. Zero-initialize before hal_open(). */
typedef struct
{
    void *base;           /**< Address of byte 0 of the file. May change on hal_grow(). */
    uint64_t size;        /**< Current size of the file and of the mapping, in bytes. */
    uintptr_t handle[2];  /**< OS handles (file and mapping, or file descriptor). Private. */
} hal_map;

/**
 * @brief Opens a file for exclusive read/write access and maps all of it.
 *
 * A file that does not exist, or is empty, is created with @p initial_size
 * zero bytes. Another process that tries to open the same file fails.
 *
 * @param m            Map to fill; must be zeroed.
 * @param path         Path of the database file.
 * @param initial_size Size for a new file, in bytes (must be non-zero).
 * @param created      Receives true if the file was new.
 * @param err          Buffer of ::HAL_ERR_MAX bytes; receives a message on failure.
 * @return 0 on success, -1 on failure (nothing is left open).
 */
int hal_open(hal_map *m, const char *path, uint64_t initial_size, bool *created, char *err);

/**
 * @brief Enlarges the file and remaps it. New bytes are zero.
 *
 * Invalidates every pointer into the old mapping. Does nothing if
 * @p new_size is not larger than the current size.
 *
 * @param m        Map to grow.
 * @param new_size New size in bytes.
 * @param err      Buffer of ::HAL_ERR_MAX bytes; receives a message on failure.
 * @return 0 on success, -1 on failure. After a failure the old mapping is
 *         restored if possible; if not, hal_map::base is NULL.
 */
int hal_grow(hal_map *m, uint64_t new_size, char *err);

/**
 * @brief Flushes all modified pages to the storage device and waits.
 * @param m   Map to flush.
 * @param err Buffer of ::HAL_ERR_MAX bytes; receives a message on failure.
 * @return 0 on success, -1 on failure.
 */
int hal_sync(hal_map *m, char *err);

/**
 * @brief Unmaps and closes the file. The map is zeroed and may be reused.
 *
 * Does not flush by itself; call hal_sync() first if durability matters.
 *
 * @param m Map to close; safe to call on a map that is not open.
 */
void hal_close(hal_map *m);

#endif
