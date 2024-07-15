#include "clist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct point {
  int x, y;
  struct intrusive_node node;
};

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

int main() {
  char operation[10];
  int x, y;
  struct intrusive_list l;
  init_list(&l);

  while (1) {
    scanf("%10s", operation);

    if (strcmp(operation, "add") == 0) {
      scanf("%d %d", &x, &y);
      add_point(&l, x, y);

      } else if (strcmp(operation, "rm") == 0) {
        scanf("%d %d", &x, &y);
        remove_point(&l, x, y);

      } else if (strcmp(operation, "rma") == 0) {
        remove_all_points(&l);

      } else if (strcmp(operation, "print") == 0) {
        show_all_points(&l);

      } else if (strcmp(operation, "len") == 0) {
        printf("%d\n", get_length(&l));

      } else if (strcmp(operation, "exit") == 0) {
        remove_all_points(&l);
        free(l.head);
        break;

      } else {
        printf("Unknown command\n");
      }
  }
  return 0;
}
