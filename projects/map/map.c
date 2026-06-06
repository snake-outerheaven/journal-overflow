#include "map.h"
#include "utils.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

map_t *
map_init (void)
{
  map_t *map = calloc (1, sizeof (map_t));

  if (!map)
    return NULL;

  map->size = 0;
  map->capacity = MAX_CAPACITY;

  return map;
}

int
map_kill (map_t **this)
{
  map_t *temp;
  node_t *curr;
  node_t *next;

  if (!this || !*this)
    return 1;

  temp = *this;

  for (size_t i = 0; i < temp->capacity; ++i)
    {
      curr = temp->mapped[i];

      while (curr)
        {
          next = curr->next;
          free (curr);
          curr = next;
        }
    }

  free (temp);

  *this = NULL;

  return 0;
}

int
map_insert (map_t *this, const char *key, const char *value)
{
  size_t index;
  node_t *walker;

  if (!this || !key || !value || strlen (key) >= MAXBUF
      || strlen (value) >= MAXBUF)
    return 1;

  index = hash (key) % this->capacity;
  walker = this->mapped[index];

  if (walker)
    {
      while (1)
        {
          if (!strcmp (walker->key, key))
            {
              strcpy (walker->value, value);
              return 0;
            }
          if (!walker->next)
            break;
          walker = walker->next;
        }
    }

  node_t *new = malloc (sizeof (*new));

  if (!new)
    return 2;

  strcpy (new->key, key);

  strcpy (new->value, value);

  new->next = NULL;

  if (!this->mapped[index])
    this->mapped[index] = new;

  else
    walker->next = new;

  this->size++;

  return 0;
}

int
map_remove (map_t *this, const char *key)
{
  size_t index;

  node_t *prev = NULL;
  node_t *current;

  if (!this || !key)
    return 1;

  index = hash (key) % this->capacity;

  current = this->mapped[index];

  while (current)
    {
      if (!strcmp (key, current->key))
        {
          if (!prev)
            this->mapped[index] = current->next;

          else
            prev->next = current->next;

          free (current);
          this->size--;
          return 0;
        }

      prev = current;
      current = current->next;
    }

  return 2;
}

int
map_get (const map_t *this, const char *key, char *out)
{
  size_t index;

  node_t *current;

  if (!this || !key || !out)
    return 1;

  index = hash (key) % this->capacity;

  if (!this->mapped[index])
    return 2;

  current = this->mapped[index];

  while (current)
    {
      if (!strcmp (key, current->key))
        {
          strcpy (out, current->value);
          return 0;
        }

      current = current->next;
    }

  return 2;
}

int
map_contains (const map_t *this, const char *key)
{
  size_t index;
  node_t *current;

  if (!this || !key)
    return 1;

  index = hash (key) % this->capacity;
  current = this->mapped[index];

  while (current)
    {
      if (!strcmp (key, current->key))
        return 0;
      current = current->next;
    }

  return 2;
}

int
map_print (const map_t *this)
{
  node_t *current;

  if (!this)
    return 1;

  printf ("Map (size: %zu, capacity: %zu):\n", this->size, this->capacity);

  for (size_t i = 0; i < this->capacity; ++i)
    {
      current = this->mapped[i];
      if (current)
        {
          printf (" [%zu]: ", i);
          while (current)
            {
              printf ("{%s: %s} ", current->key, current->value);
              current = current->next;
            }
          printf ("\n");
        }
    }
  return 0;
}

size_t
map_size (const map_t *this)
{
  return this ? this->size : 0;
}
