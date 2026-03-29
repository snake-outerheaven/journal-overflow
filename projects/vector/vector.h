#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#define BOUND_ERR (-1)
#define FUNC_OK 0
#define PARAM_ERR 1
#define DEREF_ERR 2
#define MEM_ERR 3

typedef struct vector_t vector_t;

vector_t *vec_init();
int vec_kill(vector_t **);

int vec_push(vector_t *, int);
int vec_pop(vector_t *, int *);

size_t vec_size(const vector_t *);
size_t vec_cap(const vector_t *);

#endif
