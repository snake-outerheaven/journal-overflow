#ifndef TASK_H
#define TASK_H

typedef struct task task_t;

task_t *task_init(void);
void task_delete(task_t **);

/*
 * TODO:Create getter and setters for tasks
 */

#endif
