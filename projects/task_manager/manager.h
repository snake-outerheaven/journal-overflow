#ifndef MANAGER_H
#define MANAGER_H

#include "task.h"

typedef struct manager manager_t;

manager_t *manager_init(void);

void manager_delete(manager_t **);

int manager_add(manager_t *, task_t *);

int manager_rm(manager_t *);

int manager_rm_by_id(manager_t *, int);

int manager_sort(manager_t *);

int manager_search(manager_t *, int, task_t **);

#endif
