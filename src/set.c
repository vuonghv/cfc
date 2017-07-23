#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "set.h"
#include "mem.h"

static int cmpatom(const void *x, const void *y) {
    return x != y;
}

static unsigned hashatom(const void *x) {
    return (unsigned long)x>>2;
}

struct set_t {
    int num_members;
    int num_slots;
    int (*cmp)(const void *x, const void *y);
    unsigned (*hash)(const void *x);
    struct member {
        const void *member;
        struct member *next;
    } *buckets[];
};

static int primes[] = {
    3, 7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 107, 131, 163, 197, 239, 293,
    353, 431, 521, 631, 761, 919, 1103, 1327, 1597, 1931, 2333, 2801, 3371,
    4049, 4861, 5839, 7013, 8419, 10103, 12143, 14591, 17519, 21023, 25229,
    30293, 36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437,
    187751, 225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403,
    968897, 1162687, 1395263, 1674319, 2009191, 2411033, 2893249, 3471899,
    4166287, 4999559, 5999471, 7199369, INT_MAX
};

static int num_primes = (sizeof(primes) / sizeof(primes[0]));

set_t set_new(int hint,
        int cmp(const void *x, const void *y),
        unsigned hash(const void *x)) {
    assert(hint >= 0);
    int i;
    for (i = 0; primes[i] < hint; i++);

    set_t set = ALLOC(sizeof(*set) + primes[i]*sizeof(set->buckets[0]));
    set->num_slots = primes[i];
    set->num_members = 0;
    set->cmp = cmp ? cmp : cmpatom;
    set->hash = hash ? hash : hashatom;
    for (i = 0; i < set->num_slots; i++) {
        set->buckets[i] = NULL;
    }
    return set;
}

void set_free(set_t *set) {
    assert(set && *set);
    if ((*set)->num_members > 0) {
        struct member *p, *q;
        for (int i = 0; i < (*set)->num_slots; i++) {
            for (p = (*set)->buckets[i]; p; p=q) {
                q = p->next;
                FREE(p);
            }
        }
    }
    FREE(*set);
}

int set_size(set_t set) {
    assert(set);
    return set->num_members;
}

bool set_empty(set_t set) {
    assert(set);
    return set->num_members == 0;
}

bool set_contains(set_t set, const void *member) {
    assert(set);
    assert(member);
    int slot = set->hash(member) % set->num_slots;
    struct member *p;
    for (p = set->buckets[slot]; p; p = p->next) {
        if (set->cmp(p->member, member) == 0) return true;
    }
    return false;
}

void set_put(set_t set, const void *member) {
    assert(set);
    assert(member);
    int slot = set->hash(member) % set->num_slots;
    struct member *p;
    for (p = set->buckets[slot]; p; p = p->next) {
        if (set->cmp(p->member, member) == 0) break;
    }

    if (p == NULL) {
        NEW(p);
        p->member = member;
        p->next = set->buckets[slot];
        set->buckets[slot] = p;
        set->num_members++;
    } else {
        p->member = member;
    }
}

void *set_remove(set_t set, const void *member) {
    assert(set);
    assert(member);
    int slot = set->hash(member) % set->num_slots;
    struct member **pp;
    for (pp = &set->buckets[slot]; *pp; pp = &(*pp)->next) {
        if (set->cmp((*pp)->member, member) == 0) {
            struct member *p = *pp;
            *pp = (*pp)->next;
            member = p->member;
            FREE(p);
            set->num_members--;
            return (void *)member;
        }
    }
    return NULL;
}
