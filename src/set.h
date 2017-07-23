#ifndef POSEIDON_SET_INCLUDE_H
#define POSEIDON_SET_INCLUDE_H

#include <stdbool.h>

typedef struct set_t *set_t;

set_t set_new(int hint,
              int cmp(const void *x, const void *y),
              unsigned hash(const void *x));

void set_free(set_t *set);
int set_size(set_t set);
bool set_empty(set_t set);
bool set_contains(set_t set, const void *member);
void set_put(set_t set, const void *member);
void *set_remove(set_t set, const void *member);

#endif
