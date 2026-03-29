#include "vector.h"

#include <stddef.h>
#include <stdlib.h>

#define INIT_CAPACITY 32

struct vector_t
{
    int *data;
    size_t size;
    size_t capacity;
};

vector_t *vec_init()
{
    vector_t *v;

    v = malloc(sizeof(*v));

    if (!v)
        return NULL;

    v->data = malloc(INIT_CAPACITY * sizeof(*v->data));

    if (!v->data)
    {
        free(v);
        return NULL;
    }

    v->size = 0;
    v->capacity = INIT_CAPACITY;

    return v;
}

int vec_kill(vector_t **v)
{
    vector_t *tmp;

    if (!v)
        return PARAM_ERR;

    if (!*v)
        return DEREF_ERR;

    tmp = *v;

    free(tmp->data);
    tmp->size = 0;
    tmp->capacity = 0;

    free(tmp);

    *v = NULL;

    return FUNC_OK;
}

int vec_push(vector_t *v, int item)
{
    int *tmp;
    size_t newcap;

    if (!v)
        return PARAM_ERR;

    if (!v->data || !v->capacity)
        return PARAM_ERR;

    if (v->size >= v->capacity)
    {
        newcap = v->capacity * 2;

        tmp = realloc(v->data, newcap * sizeof(*v->data));

        if (!tmp)
            return MEM_ERR;

        v->data = tmp;

        v->capacity = newcap;
    }

    v->data[v->size++] = item;

    return FUNC_OK;
}

int vec_pop(vector_t *v, int *out)
{
    if (!v || !out)
        return PARAM_ERR;

    if (!v->data)
        return DEREF_ERR;

    if (v->size <= 0)
        return PARAM_ERR;


    *out = v->data[--v->size];

    return FUNC_OK;
}

size_t vec_size(const vector_t *v)
{
    return v ? v->size : 0;
}

size_t vec_cap(const vector_t *v)
{
    return v ? v->capacity : 0;
}
