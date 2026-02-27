#ifndef MANAGER_H
#define MANAGER_H

#include "task.h"

#include <stddef.h>

typedef struct manager manager_t;

manager_t *manager_init(void);

void manager_delete(manager_t **);

int manager_add(manager_t *, task_t *);

int manager_rm(manager_t *);

int search_and_retrieve(const manager_t *, task_t **, const size_t);

#endif
