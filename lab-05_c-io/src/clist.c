#include "clist.h"


void init_list(intrusive_list_t *list) {
    list->head.next = NULL;
    list->head.prev = NULL;
}

intrusive_node_t * find_tail(intrusive_list_t *list) {
	intrusive_node_t * tail = &list->head;
	while (tail->next)
		tail = tail->next;
	return tail;
}

void add_node(intrusive_list_t *list, intrusive_node_t *node) {
	intrusive_node_t *tail = find_tail(list);
    tail->next = node;
    node->prev = tail;
}

void remove_node(intrusive_node_t *node) {
    node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
}

int get_length(intrusive_list_t *list) {
    intrusive_node_t *node = &list->head;
    int length = 0;
    while (node->next) {
        length++;
        node = node->next;
    }
    return length;
}


void apply(intrusive_list_t *list, void (*op)(intrusive_node_t *node, void *data), void *data) {
    intrusive_node_t *node = list->head.next;
    while (node) {
        op(node, data);
        node = node->next;
    }
}
