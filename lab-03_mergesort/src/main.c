#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "mergesort.h"

int cmp_int(const void *p1, const void *p2) {
    return *(int*)p1 - *(int*)p2;
}

int cmp_char(const void *p1, const void *p2) {
    return *(char*)p1 - *(char*)p2;
}

int cmp_str(const void *p1, const void *p2) {
    return strcmp(*(char**)p1, *(char**)p2);
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        printf("\n");
        return 0;
    }
    void* array = argv + 2;

    if(strcmp(argv[1], "int") == 0) {
        array = malloc(sizeof(int) * (argc - 2));
        for (int i = 0; i < argc - 2; i++) {
            ((int*)array)[i] = atoi(argv[i + 2]);
        }
        if (my_mergesort(array, argc - 2, sizeof(int), cmp_int, 0, argc - 3) == -1) {
            printf("Error: memory allocation failed.");
            free(array);
            return 1;
        }
        for (int i = 0; i < argc - 3; i++) {
            printf("%d ", ((int*)array)[i]);
        }
        printf("%d", ((int*)array)[argc - 3]);
    }

    if(strcmp(argv[1], "char") == 0) {
        array = malloc(sizeof(char) * (argc - 2)); 
        for (int i = 0; i < argc - 2; i++) {
            ((char*)array)[i] = argv[i + 2][0];
        }
        if (my_mergesort(array, argc - 2, sizeof(char), cmp_char, 0, argc - 3)) {
            printf("Error: memory allocation failed.");
            free(array);
            return 1;
        }
        for (int i = 0; i < argc - 3; i++) {
            printf("%c ", ((char*)array)[i]);
        }
        printf("%c", ((char*)array)[argc - 3]);
    }

    if(strcmp(argv[1], "str") == 0) {
        array = malloc(sizeof(char*) * (argc - 2)); 
        for (int i = 0; i < argc - 2; i++) {
            ((char**)array)[i] = argv[i + 2];
        }
        if (my_mergesort(array, argc - 2, sizeof(char*), cmp_str, 0, argc - 3)) {
            printf("Error: memory allocation failed.");
            free(array);
            return 1;
        }
        for (int i = 0; i < argc - 3; i++) {
            printf("%s ", ((char**)array)[i]);
        }
        printf("%s", ((char**)array)[argc - 3]);
    }
    
    printf("\n");
    free(array);

    return 0;
}

