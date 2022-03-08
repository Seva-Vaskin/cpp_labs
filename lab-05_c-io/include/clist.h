#ifndef CLIST_H_
#define CLIST_H_

#include <stddef.h>

#define container_of(ptr, type, member) ((type*)((char*)(ptr) - offsetof(type, member)))

typedef struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
} intrusive_node_t;

typedef struct intrusive_list {
    intrusive_node_t head;
} intrusive_list_t;

void init_list(intrusive_list_t *);

void add_node(intrusive_list_t *, intrusive_node_t *);

void remove_node(intrusive_node_t *);

int get_length(intrusive_list_t *);

void apply(intrusive_list_t *list, void (*op)(intrusive_node_t *node, void *data), void *data);

intrusive_node_t * find_tail(intrusive_list_t *list);

#endif
