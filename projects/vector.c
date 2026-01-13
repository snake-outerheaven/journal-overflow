#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
        this file will hold the implementations of vector.h
*/

struct vector
{
    void *data;
    size_t size;
    size_t elem_size;
    size_t capacity;
};

/*
    Receives a vector from the stack, makes it manage a heap pointer to raw
   memory, initializing it properly and return meaningful status messages to the
   caller.
*/

int vector_init(Vector *v, size_t elem_size, size_t init_capacity)
{
    v->data = malloc(elem_size * init_capacity);

    if (init_capacity == 0)
    {
        v->data = NULL;
        v->size = 0;
        v->elem_size = 0;
        v->capacity = 0;
        return 2;
    }

    if (!v->data)
    {
        perror("failed to alloc memory to vector");
        return 1;
    }

    v->size = 0; /* it follows common array logic.*/
    v->elem_size = elem_size;
    v->capacity = init_capacity;

    return 0;
}

int vector_append(Vector *v, void *p)
{
    void *newdata;
    char *dest;

    if (!v || !p)
        return 1;

    if (v->size == v->capacity)
    {
        newdata = realloc(v->data, v->elem_size * v->capacity * 2);
        if (newdata == NULL)
            return 2;
        v->data = newdata;
        v->capacity *= 2;
    }

    /* need to cast raw memory to char memory
     in order to use pointer arithmetics*/
    dest = (char *)v->data + v->size * v->elem_size;

    memcpy(dest, p, v->elem_size);

    v->size++;

    return 0;
}

void *vector_read(Vector *v, size_t i, void *dest)
{
    char *src;

    if (v->size == 0)
        return 2;

    if (i >= v->size)
        return 1;

    /* the pattern of just casting void * to char * to memory makes a
     * reappearence.*/
    src = (char *)v->data + i * v->elem_size;

    memcpy(dest, src, v->elem_size);

    return 0;
}

int vector_drop(Vector *v, size_t i)
{
    char *walker;

    if (i >= v->size)
        return 1;

    if (v->size == 0)
        return 2;

    walker = (char *)v->data + i * v->elem_size;

    memset(walker, 0, v->elem_size);

    return 0;
}