// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

// computes a hash value for a given string key.
// returns an unsigned integer suitable for indexing buckets.
size_t hash_string(const char *);

#endif
