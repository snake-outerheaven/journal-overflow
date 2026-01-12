#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
        this file will hold the implementations of task.h
*/

struct task
{
    int id;
    int done;
    char taskname[50];
    char taskdescription[250];
};

struct tasknode
{
    struct task *task;
    struct tasknode *prev;
    struct tasknode *next;
};

struct tasklist
{
    struct tasknode *head;
    struct tasknode *tail;
    int size;
    int capacity;
};

Task *task_create(const char *nm, const char *desc, const int done)
{
    static int id = 0;
    Task *t;

    t = (Task *)malloc(sizeof(Task)); /* explicit typecasting, why not? */

    if (!t)
    {
        perror("malloc");
        return NULL;
    }

    t->id = id++;
    strncpy(t->taskname, nm, sizeof(t->taskname) - 1);
    t->taskname[sizeof(t->taskname) - 1] = '\0';
    strncpy(t->taskdescription, desc, sizeof(t->taskdescription) - 1);
    t->taskdescription[sizeof(t->taskdescription) - 1] = '\0';
    t->done = done;

    return t;
}