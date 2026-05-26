#include "alloc.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAXMEMORY 1024

struct alloc_t
{
  char buf[MAXMEMORY];
  size_t offset;
};

int
alloc_init (alloc_t *alloc)
{
  memset (alloc->buf, 0, MAXMEMORY);
  alloc->offset = 0;
  return 0;
}

int
alloc_kill (alloc_t *alloc)
{
  alloc->offset = 0;
  return 0;
}

void *
alloc_alloc (alloc_t *alloc, size_t siz)
{
  void *ptr;

  if ((alloc->offset + siz) >= MAXMEMORY)
    return NULL;

  ptr = &alloc->buf[alloc->offset];
  alloc->offset += siz;

  return ptr;
}