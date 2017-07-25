#include <string.h>
#include <assert.h>
#include "../src/set.h"

unsigned hash_str(const void *key) {
    char *s = (char *)key;
    unsigned int h = 31;
    for (; *s; s++) {
        h ^= ((h<<5) + (*s) + (h>>2));
    }
    return h & 0x7fffffff;
}

int cmp_str(const void *x, const void *y) {
    return strcmp(x, y);
}

int main(void) {
    set_t set = set_new(10, cmp_str, hash_str);

    assert(set_size(set) == 0);
    assert(set_empty(set));

    set_put(set, "deadpool");
    set_put(set, "batman");
    set_put(set, "spiderman");
    set_put(set, "ironman");

    assert(set_size(set) == 4);
    assert(set_contains(set, "deadpool"));
    assert(set_contains(set, "batman"));
    assert(set_contains(set, "spiderman"));
    assert(set_contains(set, "ironman"));

    set_remove(set, "ironman");

    assert(set_size(set) == 3);
    assert(!set_contains(set, "ironman"));

    set_free(&set);

    assert(set == NULL);
}
