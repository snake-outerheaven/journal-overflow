#include "manager.h"
#include "task.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

struct manager
{
    task_t **tasks;
    size_t size;
    size_t capacity;
};

manager_t *manager_init(void)
{
    size_t init_cap = (size_t)INITIAL_CAPACITY;
    manager_t *m = malloc(sizeof(struct manager));

    if (!m)
        return NULL;

    m->tasks = malloc(sizeof(task_t *) * init_cap);
    if (!m->tasks)
    {
        free(m);
        return NULL;
    }
    m->size = 0;
    m->capacity = init_cap;

    return m;
}

void manager_delete(manager_t **m)
{
    size_t i;

    if (!m)
        return;

    if (!*m)
        return;

    for (i = 0; i < (*m)->size; i++)
        task_delete(&(*m)->tasks[i]);

    free((*m)->tasks);
    free(*m);
    *m = NULL;
}

int manager_add(manager_t *m, task_t *t)
{
    task_t **tmp = NULL;
    size_t new_cap = 0;

    if (!m || !t)
        return 1;

    if (m->size >= m->capacity)
    {
        new_cap = m->capacity * 2;

        tmp = realloc(m->tasks, sizeof(task_t *) * new_cap);

        if (!tmp)
            return 2;

        m->tasks = tmp;
        m->capacity = new_cap;
    }

    m->tasks[m->size] = t;
    m->size++;

    return 0;
}

int manager_rm(manager_t *m)
{
    if (!m)
        return 1;

    if (!m->size)
        return 2;

    task_delete(&m->tasks[m->size - 1]);

    m->size--;

    return 0;
}

int manager_rm_by_id(manager_t *m, int target)
{
    size_t i;
    int id;

    if (!m)
        return 1;

    for (i = 0; i < m->size; i++)
    {
        if (task_get_id(m->tasks[i], &id))
            return 2;

        if (id == target)
        {
            task_delete(&m->tasks[i]);

            memmove(m->tasks + i, m->tasks + i + 1,
                    (m->size - 1 - i) * sizeof(task_t *));

            m->size--;

            return 0;
        }
    }
    return 3;
}

int manager_sort(manager_t *m)
{
    int id1, id2;
    size_t x, y;
    task_t *temp;

    if (!m)
        return 1;

    for (x = m->size - 1; x > 0; x--)
        for (y = 1; y <= x; y++)
        {
            if (task_get_id(m->tasks[y], &id1) ||
                task_get_id(m->tasks[y - 1], &id2))
                return 2;

            if (id1 > id2)
            {
                temp = m->tasks[y - 1];
                m->tasks[y - 1] = m->tasks[y];
                m->tasks[y] = temp;
            }
        }
    return 0;
}

int manager_search(manager_t *m, int target, task_t **t) {
    size_t i;
    int id;

    if (!m || !t)
        return 1;

    for (i = 0; i < m->size; i++)
    {
        if (task_get_id(m->tasks[i], &id))
            return 2;

        if (id == target)
        {
            *t = m->tasks[i];
            return 0;
        }
    }

    return 3;
}
