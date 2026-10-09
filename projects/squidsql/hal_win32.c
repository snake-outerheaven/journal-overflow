/**
 * @file hal_win32.c
 * @brief Windows implementation of the HAL (CreateFileMapping / MapViewOfFile).
 *
 * VirtualAlloc only hands out anonymous memory, so a file-backed region needs
 * a file mapping object instead.
 */
#include "hal.h"

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdio.h>
#include <string.h>

/** Index of the file handle in hal_map::handle. */
#define H_FILE 0
/** Index of the file-mapping handle in hal_map::handle. */
#define H_MAP 1

/**
 * @brief Writes "what (error N)" with the current Win32 error into @p err.
 * @param err  Message buffer of ::HAL_ERR_MAX bytes.
 * @param what What failed.
 * @return Always -1.
 */
static int win_error(char *err, const char *what)
{
    snprintf(err, HAL_ERR_MAX, "%s (win32 error %lu)", what, (unsigned long)GetLastError());
    return -1;
}

/**
 * @brief Sets the length of the file.
 * @param file Open file handle.
 * @param size New length in bytes.
 * @return Non-zero on success.
 */
static BOOL set_file_size(HANDLE file, uint64_t size)
{
    LARGE_INTEGER pos;

    pos.QuadPart = (LONGLONG)size;
    return SetFilePointerEx(file, pos, NULL, FILE_BEGIN) && SetEndOfFile(file);
}

/**
 * @brief Maps the first @p size bytes of the open file read/write.
 * @param m    Map whose file handle is open; base, size and mapping are set.
 * @param size Bytes to map; must not exceed the file size.
 * @param err  Message buffer.
 * @return 0 on success, -1 on failure (m->base is left NULL).
 */
static int map_view(hal_map *m, uint64_t size, char *err)
{
    HANDLE mapping;
    void *view;

    m->base = NULL;
    mapping = CreateFileMappingA((HANDLE)m->handle[H_FILE], NULL, PAGE_READWRITE, (DWORD)(size >> 32),
                                 (DWORD)(size & 0xFFFFFFFFu), NULL);
    if (!mapping)
    {
        return win_error(err, "CreateFileMapping failed");
    }
    view = MapViewOfFile(mapping, FILE_MAP_WRITE, 0, 0, 0);
    if (!view)
    {
        win_error(err, "MapViewOfFile failed");
        CloseHandle(mapping);
        return -1;
    }
    m->handle[H_MAP] = (uintptr_t)mapping;
    m->base = view;
    m->size = size;
    return 0;
}

int hal_open(hal_map *m, const char *path, uint64_t initial_size, bool *created, char *err)
{
    HANDLE file;
    LARGE_INTEGER size;

    file = CreateFileA(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE)
    {
        return win_error(err, "cannot open database file");
    }
    if (!GetFileSizeEx(file, &size))
    {
        win_error(err, "GetFileSizeEx failed");
        CloseHandle(file);
        return -1;
    }

    *created = size.QuadPart == 0;
    if (*created)
    {
        size.QuadPart = (LONGLONG)initial_size;
        if (!set_file_size(file, initial_size))
        {
            win_error(err, "cannot size database file");
            CloseHandle(file);
            return -1;
        }
    }

    memset(m, 0, sizeof *m);
    m->handle[H_FILE] = (uintptr_t)file;
    if (map_view(m, (uint64_t)size.QuadPart, err))
    {
        CloseHandle(file);
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
    UnmapViewOfFile(m->base);
    CloseHandle((HANDLE)m->handle[H_MAP]);
    m->base = NULL;

    if (!set_file_size((HANDLE)m->handle[H_FILE], new_size))
    {
        win_error(err, "cannot grow database file");
        map_view(m, old_size, err); /* best effort: restore the old mapping */
        win_error(err, "cannot grow database file");
        return -1;
    }
    return map_view(m, new_size, err);
}

int hal_sync(hal_map *m, char *err)
{
    if (!FlushViewOfFile(m->base, 0))
    {
        return win_error(err, "FlushViewOfFile failed");
    }
    if (!FlushFileBuffers((HANDLE)m->handle[H_FILE]))
    {
        return win_error(err, "FlushFileBuffers failed");
    }
    return 0;
}

void hal_close(hal_map *m)
{
    if (m->base)
    {
        UnmapViewOfFile(m->base);
    }
    if (m->handle[H_MAP])
    {
        CloseHandle((HANDLE)m->handle[H_MAP]);
    }
    if (m->handle[H_FILE])
    {
        CloseHandle((HANDLE)m->handle[H_FILE]);
    }
    memset(m, 0, sizeof *m);
}

#else

/* ISO C forbids an empty translation unit */
typedef int hal_win32_not_used;

#endif
