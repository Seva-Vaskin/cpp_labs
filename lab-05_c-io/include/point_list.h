#ifndef POINT_LIST_H
#define POINT_LIST_H

#include "clist.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct point {
    int x, y;
    intrusive_node_t node;
} point_t;

#define node_to_point(ptr) container_of(ptr, point_t, node)

void add_point(intrusive_list_t *list, int x, int y);

void remove_point(intrusive_list_t *list, int x, int y); // removes all (x, y) pairs

void show_all_points(intrusive_list_t *list);

void remove_all_points(intrusive_list_t *list);

#endif