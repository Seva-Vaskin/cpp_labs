#include "clist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct point {
    int x, y;
    intrusive_node_t node;
} point_t;

#define node_to_point(ptr) container_of(ptr, point_t, node)

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
        intrusive_node_t*next = n->next;
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
        intrusive_node_t*next = n->next;
        remove_node(n);
        free(node_to_point(n));
        n = next;
    }
}

int main() {

    intrusive_list_t list;
    init_list(&list);

    char buf[256];

    do {
        scanf("%256s", buf);
        if (strcmp(buf, "add") == 0) {
            int x, y;
            scanf("%9d %9d", &x, &y);
            add_point(&list, x, y);
        }
        else if (strcmp(buf, "rm") == 0) {
            int x, y;
            scanf("%9d %9d", &x, &y);
            remove_point(&list, x, y);
        }
        else if (strcmp(buf, "rma") == 0) {
            remove_all_points(&list);
        }
        else if (strcmp(buf, "print") == 0) {
            show_all_points(&list);
        }
        else if (strcmp(buf, "len") == 0) {
            printf("%d\n", get_length(&list));
        }
        else if (strcmp(buf, "exit") != 0) {
            printf("Unknown command\n");
        }
    } while (strcmp(buf, "exit") != 0);
    remove_all_points(&list);
    return 0;
}
