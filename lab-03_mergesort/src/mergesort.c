#include <stddef.h>
#include <stdlib.h>

int merge(
    void *array, 
    size_t element_size,
    int (*comparator)(const void *, const void *),
    size_t l, size_t m, size_t r
    ) {
        size_t i, j, k;
        size_t n1 = m - l + 1;
        size_t n2 = r - m;
        void *L = malloc(n1*element_size);
        if (L == NULL){
            free(L);

            return -1;
        }

        void *R = malloc(n2*element_size);
        if (R == NULL){
            free(R);

            return -1;
        }

        for (i = 0; i < n1; i++) {
            for (size_t s = 0; s < element_size; s++) {
                ((char*)L)[i*element_size + s] = ((char*)array)[(l+i)*element_size + s];
            }
        }
        for (j = 0; j < n2; j++) {
            for (size_t s = 0; s < element_size; s++) {
                ((char*)R)[j*element_size + s] = ((char*)array)[(m+1+j)*element_size + s];
            }
        }
        
        i = 0;
        j = 0;
        k = l;

        while (i < n1 && j < n2) {
            if (comparator(&((char*)L)[i*element_size],&((char*)R)[j*element_size]) <= 0) {
                for (size_t s = 0; s < element_size; s++) {
                    ((char*)array)[k*element_size + s] = ((char*)L)[i*element_size + s];
                }
                i++;
            }
            else {
                for (size_t s = 0; s < element_size; s++) {
                    ((char*)array)[k*element_size + s] = ((char*)R)[j*element_size + s];
                }
                j++;
            }
            k++;
        }

        while (i < n1) {
            for (size_t s = 0; s < element_size; s++) {
                ((char*)array)[k*element_size + s] = ((char*)L)[i*element_size + s];
            }
            i++;
            k++;
        }

        while (j < n2) {
            for (size_t s = 0; s < element_size; s++) {
                ((char*)array)[k*element_size + s] = ((char*)R)[j*element_size + s];
            }
            j++;
            k++;
        }

        free(R);
        free(L);

        return 0;
    };

int my_mergesort(
    void *array,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *),
    size_t l,
    size_t r
) {
    if (l < r) {
        size_t m = l + (r - l) / 2;
        
        if (my_mergesort(array, elements, element_size, comparator, l, m) == -1) {
            return -1;
        }
        if (my_mergesort(array, elements, element_size, comparator, m + 1, r) == -1) {
            return -1;
        };
        if (merge(array, element_size, comparator, l, m, r) == -1) {
            return -1;
        };
    }
    return 0;
};