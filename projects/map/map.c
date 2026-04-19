#include "map.h"
#include "utils.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 35

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

int map_kill(map_t **this)
{
    if (!this || !*this)
        return 1;

    map_t *temp = *this;

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

    *this = NULL;

    return 0;
}

int map_insert(map_t *this, const char *key, const char *value)
{
    size_t index;
    node_t *walker;

    if (!this || !key || !value)
        return 1;

    index = hash(key) % this->capacity;
    walker = this->mapped[index];

    if (walker)
    {
        while (1)
        {
            if (!strcmp(walker->key, key))
            {
                strcpy(walker->value, value);
                return 0;
            }
            if (!walker->next)
                break;
            walker = walker->next;
        }
    }

    node_t *new = malloc(sizeof(*new));

    if (!new)
        return 2;

    strcpy(new->key, key);

    strcpy(new->value, value);

    new->next = NULL;

    if (!this->mapped[index])
        this->mapped[index] = new;

    else
        walker->next = new;

    return 0;
}
