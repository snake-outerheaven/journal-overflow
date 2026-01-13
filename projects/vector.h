#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>

/* void * vector  to any data, generic datastruct. */
typedef struct vector Vector;

/* return status based on how the vector behaves when initialized*/
/* since the vector holds raw memory (void **), it needs the size_element*/
int vector_init(Vector *, size_t, size_t);

/* grabs a raw pointer and adds it to the vector.*/
int vector_append(Vector *, void *);

/* returns a copy to a item, in the vector at its index*/
void *vector_read(Vector *, size_t, void *);

/* returns status based if dropping the last element in the vector to oblivion is
 * possible*/
int vector_drop(Vector *, size_t);

#endif
