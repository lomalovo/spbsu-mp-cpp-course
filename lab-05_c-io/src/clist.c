#include "clist.h"
#include <stdlib.h>
#include <stddef.h>

void init_list(struct intrusive_list *list){
    struct intrusive_node *head = (struct intrusive_node*)malloc(sizeof(struct intrusive_node));
    head->next = NULL;
    head->prev = NULL;
    list->head = head;
};

void add_node(struct intrusive_list *list, struct intrusive_node *node){
    if (list->head->next != NULL) {
        struct intrusive_node *next = list->head->next;
        node->next = next;
        next->prev = node;
        list->head->next = node;
        node->prev = list->head;
    }
    else{
        node->next = NULL;
        list->head->next = node;
        node->prev = list->head;
    } 
};

int remove_node(struct intrusive_node *node){
    struct intrusive_node *prev = node->prev;
    struct intrusive_node *next = node->next;

    if (prev == NULL) {
        return 1;
    }

    if (next == NULL) {
        prev->next = NULL;

        return 0;
    }

    prev->next = next;
    next->prev = prev;

    return 0;
};

int get_length(struct intrusive_list *list){
    int count = 0;
    struct intrusive_node *curr = list->head;

    while (curr->next != NULL){
        count += 1;
        curr = curr->next;
    }

    return count;
};

void apply(struct intrusive_list *list, void (*op)(struct intrusive_node* node, void* data), void* data) {
    struct intrusive_node *curr = list->head;

    while (curr->next != NULL) {
        curr = curr->next;
    }
    
    curr = curr->prev;
    
    if (curr != NULL) {
        while (curr->prev != NULL) {
            op(curr->next, data);    
            curr = curr->prev;
        }

        op(curr->next, data);
    }

};