#include "task.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXBUF 256

struct task_t
{
    int id;
    char desc[MAXBUF];
    unsigned priority;
    time_t created_at;
    time_t last_edited_at;
};

task_t *task_init()
{
    task_t *t;
    t = (task_t *)calloc(1, sizeof(struct task_t));

    if (!t)
        return NULL;

    t->id = -1;
    task_setCreatedAt(t, time(0));
    task_setLastEditedAt(t, time(0));

    return t;
}

int task_del(task_t **t)
{
    if (!t || !*t)
        return 1;

    free(*t);
    *t = NULL;

    return 0;
}

int task_setId(task_t *t, const int id)
{
    if (!t)
        return 1;

    t->id = id;
    return task_setLastEditedAt(t, time(0));
}

int task_getId(const task_t *t, int *out)
{
    if (!t || !out)
        return 1;

    *out = t->id;
    return 0;
}

int task_setDesc(task_t *t, const char *desc)
{
    if (!t || !desc)
        return 1;

    if (strlen(desc) > (MAXBUF - 1))
        return 2;

    strcpy(t->desc, desc);
    return task_setLastEditedAt(t, time(0));
}

int task_getDesc(const task_t *t, char *out)
{
    if (!t || !out)
        return 1;

    strcpy(out, t->desc);
    return 0;
}

int task_setPriority(task_t *t, const unsigned pri)
{
    if (!t)
        return 1;

    t->priority = pri;
    return task_setLastEditedAt(t, time(0));
}

int task_getPriority(const task_t *t, unsigned *out)
{
    if (!t || !out)
        return 1;

    *out = t->priority;
    return 0;
}

int task_setCreatedAt(task_t *t, const time_t cat)
{
    if (!t)
        return 1;

    t->created_at = cat;
    return 0;
}

int task_getCreatedAt(const task_t *t, time_t *out)
{
    if (!t || !out)
        return 1;

    *out = t->created_at;
    return 0;
}

int task_setLastEditedAt(task_t *t, const time_t lat)
{
    if (!t)
        return 1;

    t->last_edited_at = lat;
    return 0;
}

int task_getLastEditedAt(const task_t *t, time_t *out)
{
    if (!t || !out)
        return 1;

    *out = t->last_edited_at;
    return 0;
}

int task_getData(const task_t *t)
{
    if (!t)
        return 1;

    printf("ID: %d | Priority: %u | Desc: %s\n", t->id, t->priority, t->desc);
    printf("Created: %s", ctime(&t->created_at));
    printf("Edited:  %s", ctime(&t->last_edited_at));

    return 0;
}
