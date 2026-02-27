#include "manager.h"
#include "task.h"

#include <stddef.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10


struct manager
{
	task_t **tasks;
	size_t size;
	size_t capacity;
};


manager_t *manager_init(void)
{
	size_t init_cap = (size_t)INITIAL_CAPACITY;
	manager_t *m = malloc(sizeof(struct manager));


	if(!m)
		return NULL;

	m->tasks = malloc(sizeof(task_t *) * init_cap);
	if(!m->tasks)
	{
		free(m);
		return NULL;
	}
	m->size = 0;
	m->capacity = init_cap;

	return m;
}

void manager_delete(manager_t **m)
{
	size_t i;

	if(!m)
		return;

	if(!*m)
		return;


	for(i = 0; i < m->size; i++)
		task_delete((*m)->tasks[i]);


	free((*m)->tasks);
	free(*m);
	*m = NULL;
}

int manager_add(manager_t *m, task_t *t)
{
	task_t **tmp = NULL;
	size_t new_cap = 0;

	if(!m || !t)
		return 1;

	if(m->size >= m->capacity)
	{
		new_cap = m->capacity * 2;

		tmp = realloc(m->tasks, sizeof(task_t *) * new_cap);

		if(!tmp)
			return 2;

		m->tasks = tmp;
		m->capacity = new_cap;
	}

	m->tasks[m->size] = t;
	m->size++;

	return 0;
}

int manager_rm(manager_t *m, task_t **t)
{
	if(!m || !t)
		return 1;

	if(!m->size)
		return 2;

	*t = m->tasks[m->size - 1];

	m->tasks[m->size - 1] = NULL;

	m->size--;

	return 0;
}

int search_and_retrieve(const manager_t *m, task_t **t, const size_t target)
{
	if(!m || !t)
		return 1;

	if(target >= m->size)
		return 2;

	*t = m->tasks[target];

	return 0;
}

