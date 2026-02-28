#include "task.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUF 256
#define MIN_ID 1
#define MAX_ID 1024


struct task
{
	char taskname[MAXBUF];
	char desc[MAXBUF];
	int id;
	int done;
};


task_t *task_init(void)
{
	task_t *t;

	t = calloc(1, sizeof(struct task));

	if(!t)
		return NULL;

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

int task_set_taskname(task_t *t, char *in)
{
	if(!t || !in)
		return 1;

	strncpy(t->taskname, in, MAXBUF - 1);

	t->taskname[MAXBUF - 1] = '\0';

	return 0;
}

int task_get_desc(const task_t *t, char *out)
{
	if(!t || !out)
		return 1;

	strncpy(out, t->desc, MAXBUF - 1);

	out[MAXBUF - 1] = '\0';

	return 0;
}

int task_set_desc(task_t *t, char *in)
{
	if(!t || !in)
		return 1;

	strncpy(t->desc, in, MAXBUF - 1);

	t->desc[MAXBUF - 1] = '\0';

	return 0;
}

int task_get_done(const task_t *t, int *out)
{
	if(!t || !out)
		return 1;

	*out = t->done;

	return 0;
}

int task_set_done(task_t *t, int in)
{
	if(!t)
		return 1;

	t->done = in;

	return 0;
}
