#include "utils.h"

#include <stddef.h>
#include <stdlib.h>
#include <time.h>

void rand_init(void)
{
	srand(time(NULL));
}

