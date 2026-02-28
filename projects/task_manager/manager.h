#ifndef MANAGER_H
#define MANAGER_H

#include "task.h"

typedef struct manager manager_t;

manager_t *manager_init(void);

void manager_delete(manager_t **);

int manager_add(manager_t *, task_t *);

int manager_rm(manager_t *, task_t **);

/*
 * TODO:Implement linear search and bubblesort by id of the tasks on the dynamic
 * 	array.
 */

#endif
