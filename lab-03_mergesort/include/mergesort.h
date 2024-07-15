#ifndef H_MERGESORT
#define H_MERGESORT
#include <stddef.h>

int my_mergesort(
    void *array,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *),
    size_t l,
    size_t r
);

#endif