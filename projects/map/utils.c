#include "utils.h"

// djb2 hash function.
// starts with a fixed seed (5381) and iteratively updates
// the hash using the formula: hash * 33 + c.
// simple and fast to compute, produces a good distribution
// for typical string keys.
size_t hash_string(const char *str)
{
    size_t hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}
