#include "map.h"
#include "utils.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 10

typedef struct node_t
{
    char key[MAXBUF];
    char value[MAXBUF];
    struct node_t *next;
} node_t;

struct map_t
{
    node_t *mapped[MAX_CAPACITY];
    size_t size;
    size_t capacity;
};

map_t *map_init(void)
{
    map_t *map = calloc(1, sizeof(map_t));

    if (!map)
        return NULL;

    map->size = 0;
    map->capacity = MAX_CAPACITY;

    return map;
}

int map_kill(map_t **map)
{
    if (!map || !*map)
        return 1;

    map_t *temp = *map;

    for (size_t i = 0; i < MAX_CAPACITY; ++i)
    {
        node_t *curr = temp->mapped[i];

        while (curr)
        {
            node_t *next = curr->next;
            free(curr);
            curr = next;
        }
    }

    free(temp);
    *map = NULL;

    return 0;
}