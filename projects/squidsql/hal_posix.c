/**
 * @file hal_posix.c
 * @brief POSIX implementation of the HAL (mmap / ftruncate / msync).
 */
#ifndef _WIN32
#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#endif

#include "hal.h"

#ifndef _WIN32

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/** Index of the file descriptor in hal_map::handle. */
#define H_FD 0

/**
 * @brief Writes "what: strerror(errno)" into @p err.
 * @param err  Message buffer of ::HAL_ERR_MAX bytes.
 * @param what What failed.
 * @return Always -1.
 */
static int sys_error(char *err, const char *what)
{
    snprintf(err, HAL_ERR_MAX, "%s: %s", what, strerror(errno));
    return -1;
}

/**
 * @brief Maps the first @p size bytes of the open file read/write.
 * @param m    Map whose descriptor is open; base and size are set.
 * @param size Bytes to map; must not exceed the file size.
 * @param err  Message buffer.
 * @return 0 on success, -1 on failure (m->base is left NULL).
 */
static int map_view(hal_map *m, uint64_t size, char *err)
{
    void *p;

    m->base = NULL;
    if (size > (uint64_t)SIZE_MAX)
    {
        snprintf(err, HAL_ERR_MAX, "database file too large for this platform");
        return -1;
    }
    p = mmap(NULL, (size_t)size, PROT_READ | PROT_WRITE, MAP_SHARED, (int)m->handle[H_FD], 0);
    if (p == MAP_FAILED)
    {
        return sys_error(err, "mmap failed");
    }
    m->base = p;
    m->size = size;
    return 0;
}

int hal_open(hal_map *m, const char *path, uint64_t initial_size, bool *created, char *err)
{
    struct stat st;
    int fd;

    fd = open(path, O_RDWR | O_CREAT, 0644);
    if (fd < 0)
    {
        return sys_error(err, "cannot open database file");
    }
    if (flock(fd, LOCK_EX | LOCK_NB) != 0)
    {
        sys_error(err, "database file is in use");
        close(fd);
        return -1;
    }
    if (fstat(fd, &st) != 0)
    {
        sys_error(err, "fstat failed");
        close(fd);
        return -1;
    }

    *created = st.st_size == 0;
    if (*created)
    {
        st.st_size = (off_t)initial_size;
        if (ftruncate(fd, st.st_size) != 0)
        {
            sys_error(err, "cannot size database file");
            close(fd);
            return -1;
        }
    }

    memset(m, 0, sizeof *m);
    m->handle[H_FD] = (uintptr_t)fd;
    if (map_view(m, (uint64_t)st.st_size, err))
    {
        close(fd);
        memset(m, 0, sizeof *m);
        return -1;
    }
    return 0;
}

int hal_grow(hal_map *m, uint64_t new_size, char *err)
{
    uint64_t old_size = m->size;

    if (new_size <= old_size)
    {
        return 0;
    }
    munmap(m->base, (size_t)old_size);
    m->base = NULL;

    if (ftruncate((int)m->handle[H_FD], (off_t)new_size) != 0)
    {
        sys_error(err, "cannot grow database file");
        map_view(m, old_size, err); /* best effort: restore the old mapping */
        sys_error(err, "cannot grow database file");
        return -1;
    }
    return map_view(m, new_size, err);
}

int hal_sync(hal_map *m, char *err)
{
    if (msync(m->base, (size_t)m->size, MS_SYNC) != 0)
    {
        return sys_error(err, "msync failed");
    }
    if (fsync((int)m->handle[H_FD]) != 0)
    {
        return sys_error(err, "fsync failed");
    }
    return 0;
}

void hal_close(hal_map *m)
{
    if (m->base)
    {
        munmap(m->base, (size_t)m->size);
    }
    if (m->handle[H_FD] || m->base)
    {
        close((int)m->handle[H_FD]);
    }
    memset(m, 0, sizeof *m);
}

#else

/* ISO C forbids an empty translation unit */
typedef int hal_posix_not_used;

#endif
