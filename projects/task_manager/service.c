#include "service.h"
#include "manager.h"
#include "task.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
