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


int task_get_id(const task_t *t, int *out)
{
	if(!t || !out)
		return 1;

	*out = t->id;

	return 0;
}

int task_set_id(task_t *t, int in)
{
	if(!t)
		return 1;

	t->id = in;

	return 0;
}

int task_get_taskname(const task_t *t, char *out)
{
	if(!t || !out)
		return 1;

	strncpy(out, t->taskname, MAXBUF - 1);

	out[MAXBUF - 1] = '\0';

	return 0;
}

int task_set_taskname(task_t *t, char *out)
{
	if(!t || !out)
		return 1;

	strncpy(t->taskname, out, MAXBUF - 1);

	t->taskname[MAXBUF - 1] = '\0';

	return 0;
}
