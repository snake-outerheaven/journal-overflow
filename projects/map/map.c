#include "map.h"
#include "utils.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    char key[MAXBUF];
    char value[MAXBUF];
    node_t *next;
} node_t;

struct map_t
{
    node_t **mapped;
    size_t size;
    size_t capacity;
};

map_t *map_init(size_t size)
{
    // calloc already initializes size and capacity to 0,
    // this behaviour is mostly cross platform
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return NULL;

    map->mapped =
        calloc(INIT_CAPACITY,
               sizeof(*map->mapped)); // inicializa matriz com ponteiros NULL.

    if (!map->mapped)
    {
        free(map);
        return NULL;
    }

    map->size = 0;
    map->capacity = INIT_CAPACITY;

    return map;
}

int map_kill(map_t **map)
{
    size_t i;
    map_t *temp;
    node_t *curr;
    node_t *next;

    if (!map)
        return 1;

    if (!*map)
        return 2;

    temp = *map;

    for (i = 0; i < temp->capacity; ++i)
    {
        curr = temp->mapped[i];

        while (curr)
        {
            next = curr->next;
            free(curr);
            curr = next;
        }
    }

    free(temp->mapped);

    free(temp);

    *map = NULL;

    return 0;
}