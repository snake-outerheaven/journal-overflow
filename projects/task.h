#ifndef TASK_H
#define TASK_H

/* This is essentialy a record. */
typedef struct task Task;

/* this is the node of the data structure*/
typedef struct tasknode TaskNode;

/* contains a pointer to the head, a pointer to the tail,
a item counter and a capacity counter.*/
typedef struct tasklist TaskList;

Task *task_create(char *, char *, int);
void task_free(Task *);

TaskList *create_tasklist(int);
void free_tasklist(TaskList *);

void tasklist_insert_head(TaskList *, Task *);
void tasklist_insert_tail(TaskList *, Task *);
void tasklist_delete_head(TaskList *, Task *);
void tasklist_delete_tail(TaskList *);
void tasklist_print_tasks(const TaskList *);

#endif
