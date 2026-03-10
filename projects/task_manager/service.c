#include "service.h"
#include "manager.h"
#include "task.h"

#include <stddef.h>
#include <stdlib.h>

struct service
{
    manager_t *mgr;
};

service_t *service_init()
{
    service_t *svc;

    svc = malloc(sizeof(struct service));

    if (!svc)
        return NULL;

    svc->mgr = manager_init();

    if (!svc->mgr)
    {
        free(svc);
        return NULL;
    }

    return svc;
}

void service_delete(service_t **svc)
{
    if (!svc)
        return;

    if (!*svc)
        return;

    manager_delete(&(*svc)->mgr);

    free(*svc);

    *svc = NULL;
}

int service_create_task(service_t *svc, const char *name, const char *desc,
                        const int id, const int done)
{
    task_t *task;
    int c1;

    if (!svc || !name || !desc)
        return 1;

    task = task_init();

    if (!task)
        return 2;

    if (task_set_taskname(task, name) || task_set_desc(task, desc) ||
        task_set_id(task, id) || task_set_done(task, done))
    {
        task_delete(&task);
        return 3;
    }

    if (manager_add(svc->mgr, task))
    {
        task_delete(&task);
        return 4;
    }

    return 0;
}

int service_delete_task(service_t *svc, const int id)
{
    if (!svc)
        return 1;

    if (manager_rm_by_id(svc->mgr, id))
        return 2;

    return 0;
}

int service_list_tasks(const service_t *svc)
{
    if (!svc)
        return 1;

    if (manager_list(svc->mgr))
        return 2;

    return 0;
}
