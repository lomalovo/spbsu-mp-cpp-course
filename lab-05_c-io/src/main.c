#include "point_list.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

void text_read(char* path, struct intrusive_list* list) {
    FILE* f = fopen(path, "r");
    int x, y;

    while (fscanf(f, "%d %d", &x, &y) == 2) {
        add_point(list, x, y);
    }
    fclose(f);
}

void text_write(char* path, struct intrusive_list* list) {
    FILE* f = fopen(path, "w");

    struct intrusive_node* curr = list->head;

    while (curr->next != NULL) {
        curr = curr->next;
    }

    if (curr->prev != NULL){
        curr = curr->prev;
    
        while (curr->prev != NULL) {
            struct point* item = container_of(curr->next, struct point, node);
            fprintf(f, "%d %d\n", item->x, item->y);
            curr = curr->prev;
        }

        if (curr->next != NULL) {
            struct point* item = container_of(curr->next, struct point, node);
            fprintf(f, "%d %d\n", item->x, item->y);
        }
    }
    
    fclose(f);
}

int convert_from(int num) {
    if (num >> 23 & 1) {
        num -= (1 << 24) ;
    }
    return num;
}

int convert_to(int num) {
    if (num < 0) {
        num = -num;
        num = (1 << 24) - num;
    }
    return num;
}

void bin_read(char* path, struct intrusive_list* list) {
    FILE* f = fopen(path, "rb");
    int x = 0, y = 0;

    while (fread(&x, 3, 1, f) == 1 && fread(&y, 3, 1, f) == 1) {
        int new_x = convert_from(x);
        int new_y = convert_from(y);
        add_point(list, new_x, new_y);
    }
    fclose(f);
}

void bin_write(char* path, struct intrusive_list* list) {
    FILE* f = fopen(path, "w");

    struct intrusive_node* curr = list->head;

    while (curr->next != NULL) {
        curr = curr->next;
    }

    if (curr->prev != NULL){
        curr = curr->prev;
    
        while (curr->prev != NULL) {
            struct point* item = container_of(curr->next, struct point, node);

            int x = convert_to(item -> x);
            int y = convert_to(item -> y);

            fwrite(&x, 3, 1, f);
            fwrite(&y, 3, 1, f);

            curr = curr->prev;
        }
        
        if (curr->next != NULL) {
            struct point* item = container_of(curr->next, struct point, node);

            int x = convert_to(item -> x);
            int y = convert_to(item -> y);

            fwrite(&x, 3, 1, f);
            fwrite(&y, 3, 1, f);
        }
    }
    
    fclose(f);
}

void print(struct intrusive_node* node_for_print, void* fmt) {
    struct point* item = container_of(node_for_print, struct point, node);
    printf((char*)fmt, item->x, item->y);
}

void count_node(struct intrusive_node *node, void* count) {
    assert(node);
    (*(int*)count)++;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        return 1;
    }

    char* type = argv[1];
    char* path_in = argv[2];
    char* action = argv[3];

    struct intrusive_list list;
    init_list(&list);

    if(strcmp(type, "loadtext") == 0){
        text_read(path_in, &list);
    }
    else {
        bin_read(path_in, &list);
    }
    
    if(strcmp(action, "savetext") == 0) {
        char* path_out = argv[4];
        text_write(path_out, &list);
    }

    if(strcmp(action, "savebin") == 0) {
        char* path_out = argv[4];
        bin_write(path_out, &list);
    }

    if(strcmp(action, "print") == 0) {
        char* fmt = argv[4];
        apply(&list, print, fmt);
        printf("\n");
    }

    if(strcmp(action, "count") == 0) {
        int size = 0;
        apply(&list, count_node, &size);
        printf("%d\n", size);
    }
    
    remove_all_points(&list);
    free(list.head);

    return 0;
}