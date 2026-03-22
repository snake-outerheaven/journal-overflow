#ifndef TASK_H
#define TASK_H

#include <time.h>

typedef struct task_t task_t;

task_t *task_init();
int task_del(task_t **);

int task_setId(task_t *, const int);
int task_getId(const task_t *, int *);

int task_setDesc(task_t *, const char *);
int task_getDesc(const task_t *, char *);

int task_setPriority(task_t *, const unsigned);
int task_getPriority(const task_t *, unsigned *);

int task_setCreatedAt(task_t *, const time_t);
int task_getCreatedAt(const task_t *, time_t *);

int task_setLastEditedAt(task_t *, const time_t);
int task_getLastEditedAt(const task_t *, time_t *);

int task_getData(const task_t *);

#endif
