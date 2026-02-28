#ifndef TASK_H
#define TASK_H

typedef struct task task_t;

task_t *task_init(void);
void task_delete(task_t **);

int task_get_id(const task_t *, int *);
int task_set_id(task_t *, int);

int task_get_taskname(const task_t *, char *);
int task_set_taskname(task_t *, char *);

int task_get_desc(const task_t *, char *);
int task_set_desc(task_t *, char *);

int task_get_done(const task_t *, int *);
int task_set_done(task_t *, int);

#endif
