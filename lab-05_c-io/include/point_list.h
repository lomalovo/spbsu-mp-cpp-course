#ifndef POINT_H_
#define POINT_H_

#include "clist.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct point {
  int x, y;
  struct intrusive_node node;
};

void add_point(struct intrusive_list *list, int x, int y);
void remove_point(struct intrusive_list *list, int x, int y);
void show_all_points(struct intrusive_list *list);
void remove_all_points(struct intrusive_list *list);

#endif