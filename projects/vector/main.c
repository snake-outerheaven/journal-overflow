#include "vector.h"

#include <stdio.h>

int main()
{
    vector_t *v = vec_init();
    int i;

    for (i = 0; i < 5000000; i++)
    {
        if (vec_push(v, i) != FUNC_OK)
        {
            printf("Falha catastrófica no item %d\n", i);
            break;
        }
    }

    printf("Tamanho final: %llu | Capacidade: %llu\n", vec_size(v), vec_cap(v));

    vec_kill(&v);
    return 0;
}
