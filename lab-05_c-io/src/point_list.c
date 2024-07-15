#include "point_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

void add_point(struct intrusive_list *list, int x, int y) {
  struct point *new_point = (struct point*)malloc(sizeof(struct point));

  new_point->x = x;
  new_point->y = y;

  add_node(list, &(new_point->node));
}

void remove_point(struct intrusive_list *list, int x, int y) { // removes all (x, y) pairs
  struct intrusive_node *curr_node = list->head->next;

  while (curr_node != NULL){
    struct point *curr_point = container_of(curr_node, struct point, node);
    curr_node = curr_node->next;
    
    if (curr_point->x == x && curr_point->y == y) {
      remove_node(&(curr_point->node));
      free(curr_point);
    }
  }
  
}

void show_all_points(struct intrusive_list *list) {
  struct intrusive_node *curr_node = list->head->next;

  if (curr_node != NULL) {
    struct point *curr_point = container_of(curr_node, struct point, node);
    printf("(%d %d)", curr_point->x, curr_point->y);

    curr_node = curr_node->next;
  }

  while (curr_node != NULL){
    struct point *curr_point = container_of(curr_node, struct point, node);
    printf(" (%d %d)", curr_point->x, curr_point->y);

    curr_node = curr_node->next;
  }

  printf("\n");
}

void remove_all_points(struct intrusive_list *list) {
  struct intrusive_node *curr_node = list->head->next;
  
  while (curr_node != NULL){
    struct point *curr_point = container_of(curr_node, struct point, node);
    struct intrusive_node *next = curr_node->next;
    
    remove_node(curr_node);
    free(curr_point);

    curr_node = next;
  }
}