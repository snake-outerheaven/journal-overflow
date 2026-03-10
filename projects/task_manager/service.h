#ifndef SERVICE_H
#define SERVICE_H

typedef struct service service_t;

service_t *service_init();

void service_delete(service_t **);

int service_create_task(service_t *, const char[], const char[], const int,
                        const int);

int service_delete_task(service_t *, const int);

int service_list_tasks(service_t *);

#endif
