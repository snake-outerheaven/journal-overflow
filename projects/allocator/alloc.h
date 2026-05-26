#ifndef ALLOC_H
#define ALLOC_H

#include <stddef.h>

typedef struct alloc_t alloc_t;

int alloc_init (alloc_t *);
int alloc_kill (alloc_t *);

void *alloc_alloc (alloc_t*, size_t);

#endif