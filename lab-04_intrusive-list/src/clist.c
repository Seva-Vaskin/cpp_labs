#include "clist.h"

void init_list(intrusive_list_t *list) {
	list->head.next = NULL;
	list->head.prev = NULL;
}

void add_node(intrusive_list_t *list, intrusive_node_t *node) {
	node->prev = &list->head;
	node->next = list->head.next;
	if (list->head.next)
		list->head.next->prev = node;
	list->head.next = node;
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