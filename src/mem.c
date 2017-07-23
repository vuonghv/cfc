#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "mem.h"

static void alloc_failed(const char *file, int line) {
    fprintf(stderr, "ERROR %s:%d: Out of memory\n", file, line);
    exit(EXIT_FAILURE);
}

void *mem_alloc(long nbytes, const char *file, int line) {
    assert(nbytes > 0);
    void *ptr = malloc(nbytes);
    if (ptr == NULL) {
        alloc_failed(file, line);
    }
    return ptr;
}

void *mem_calloc(long count, long nbytes, const char *file, int line) {
    assert(count > 0);
    assert(nbytes > 0);
    void *ptr = calloc(count, nbytes);
    if (ptr == NULL) {
        alloc_failed(file, line);
    }
    return ptr;
}

void *mem_resize(void *ptr, long nbytes, const char *file, int line) {
    assert(ptr);
    assert(nbytes > 0);
    ptr = realloc(ptr, nbytes);
    if (ptr == NULL) {
        alloc_failed(file, line);
    }
    return ptr;
}

void mem_free(void *ptr) {
    if (ptr) free(ptr);
}
