#include "task.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUF 256
#define MIN_ID 1
#define MAX_ID 1024


struct task
{
	int id;
	char taskname[MAXBUF];
	char desc[MAXBUF];
	int done;
};


task_t *task_init(void)
{
	task_t *t;

	t = malloc(sizeof(struct task));

	if(!t)
		return NULL;

	t->id = rand() % MAX_ID + MIN_ID;
	memset(t->taskname, 0, MAXBUF);
	memset(t->desc, 0, MAXBUF);
	t->done = 0;

	return t;
}

void task_delete(task_t **t)
{
	if(!t)
		return;

	if(!*t)
		return;

	free(*t);

	*t = NULL;
}
