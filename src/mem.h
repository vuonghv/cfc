#ifndef POSEIDON_MEM_INCLUDE_H
#define POSEIDON_MEM_INCLUDE_H

void *mem_alloc(long nbytes, const char *file, int line);
void *mem_calloc(long count, long nbytes, const char *file, int line);
void *mem_resize(void *ptr, long nbytes, const char *file, int line);
void mem_free(void *ptr);

#define ALLOC(nbytes) mem_alloc((nbytes), __FILE__, __LINE__)
#define CALLOC(count, nbytes) mem_calloc((count), (nbytes), __FILE__, __LINE__)
#define NEW(p) ((p) = ALLOC((long)sizeof *(p)))
#define RESIZE(p, nbytes) ((p) = mem_resize((p), (nbytes), __FILE__, __FILE__))
#define FREE(p) ((void)(mem_free((p)), (p) = NULL))

#endif
