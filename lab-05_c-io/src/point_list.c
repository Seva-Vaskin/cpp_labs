#include "point_list.h"

void add_point(intrusive_list_t *list, int x, int y) {
    point_t *p = (point_t *) malloc(sizeof(point_t));
    p->x = x;
    p->y = y;
    p->node.next = p->node.prev = NULL;
    add_node(list, &p->node);
}

void remove_point(intrusive_list_t *list, int x, int y) { // removes all (x, y) pairs
    intrusive_node_t* n = list->head.next;
    while (n) {
        intrusive_node_t* next = n->next;
        if (node_to_point(n)->x == x && node_to_point(n)->y == y) {
            remove_node(n);
            free(node_to_point(n));
        }
        n = next;
    }
}

void show_all_points(intrusive_list_t *list) {
    intrusive_node_t* n = list->head.next;
    while (n) {
        printf("(%d %d)", node_to_point(n)->x, node_to_point(n)->y);
        n = n->next;
        if (n)
            printf(" ");
    }
    printf("\n");
}

void remove_all_points(intrusive_list_t *list) {
    intrusive_node_t* n = list->head.next;
    while (n) {
        intrusive_node_t* next = n->next;
        remove_node(n);
        free(node_to_point(n));
        n = next;
    }
}