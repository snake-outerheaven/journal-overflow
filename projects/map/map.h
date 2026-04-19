#ifndef MAP_H
#define MAP_H

#include <stddef.h>

// max index for arrays
#define MAXBUF 16

// init capacity for the map
#define INIT_CAPACITY 8

// forward declaration, use it through pointers as implementation is on map.c
typedef struct map_t map_t;

// initializes a pointer of the data structure
// on the heap.
map_t *map_init(void);

// kills the data struct on the heap and nulls the caller's pointer.
int map_kill(map_t **);

// inserts a new key-value pair into the data structure.
// if the key already exists, its value is updated.
// returns non-zero on success, zero on failure.
int map_insert(map_t *, const char *, const char *);

// retrieves the value associated with a given key.
// returns NULL if the key is not found.
void *map_get(const map_t *, const char *);

// removes a key-value pair from the data structure.
// returns non-zero if the key was found and removed, zero otherwise.
int map_remove(map_t *, const char *);

// checks if a given key exists in the data structure.
// returns non-zero if found, zero otherwise.
int map_contains(const map_t *, const char *);

// returns the number of key-value pairs currently stored.
size_t map_size(const map_t *);

#endif
