#include "point_list.h"
#include <stdio.h>
#include <stdbool.h>
#include "string.h"

int to_int24(int a) {
	if (a >= 0)
		return a;
	else
		return (-a ^ 0x00ffffff) + 1;
}

int from_int24(int a) {
	if (a < (1 << 23)) 
		return a;
	else
		return -((a - 1) ^ 0x00ffffff);
}

void count_operation(intrusive_node_t *node, void *data) {
    (*((int *) data)) += node != NULL;
}

void print_operation(intrusive_node_t *node, void *data) {
    int x = node_to_point(node)->x;
    int y = node_to_point(node)->y;
    const char *format_string = (const char *) data;
    printf(format_string, x, y);
}

bool load_text(intrusive_list_t *list, char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        return 0;
    }
    int x, y;

    while (fscanf(file, "%d %d\n", &x, &y) != EOF) {
        add_point(list, x, y);
    }
    fclose(file);
    return 1;
}

bool load_binary(intrusive_list_t *list, char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        return 0;
    }

    char buf[6], x_buf[4] = {0}, y_buf[4] = {0};

    while (fread(buf, 3, 2, file)) {
        memcpy(x_buf, buf, 3);
        memcpy(y_buf, buf + 3, 3);
    	int x24 = *(int *) x_buf;
    	int y24 = *(int *) y_buf;
        int x = from_int24(x24);
        int y = from_int24(y24);
        add_point(list, x, y);
    }
    fclose(file);
    return 1;
}

bool save_text(intrusive_list_t *list, char *file_path) {
    FILE *file = fopen(file_path, "w");
    if (!file) {
        return 0;
    }

    intrusive_node_t *node = list->head.next;

    while (node) {
        int x = node_to_point(node)->x;
        int y = node_to_point(node)->y;
        fprintf(file, "%d %d\n", x, y);
        node = node->next;
    }

    fclose(file);
    return 1;
}


bool save_binary(intrusive_list_t *list, char *file_path) {
    FILE *file = fopen(file_path, "w");
    if (!file) {
        return 0;
    }

    intrusive_node_t *node = list->head.next;

    while (node) {
        int x = node_to_point(node)->x;
        int y = node_to_point(node)->y;
        int x24 = to_int24(x);
        int y24 = to_int24(y);
        fwrite(&x24, 3, 1, file);
        fwrite(&y24, 3, 1, file);
        node = node->next;
    }

    fclose(file);
    return 1;
}

int main(int argc, char **argv) {

    if (argc < 4) {
        fprintf(stderr, "not enough arguments\n");
        return 1;
    }
    bool is_binary_input = strcmp(argv[1], "loadbin") == 0;
    bool is_text_input = strcmp(argv[1], "loadtext") == 0;

    if (!is_binary_input && !is_text_input) {
        fprintf(stderr, "undefined type of input file (loadtext/loadbin expected)\n");
        return 1;
    }

    intrusive_list_t list;
    init_list(&list);

    if (is_text_input) {
        if (!load_text(&list, argv[2])) {
            fprintf(stderr, "unable to open file %s\n", argv[2]);
            return 1;
        }
    } else if (is_binary_input) {
        if (!load_binary(&list, argv[2])) {
            fprintf(stderr, "unable to open file %s\n", argv[2]);
            return 1;
        }
    }

    bool is_save_text = strcmp(argv[3], "savetext") == 0;
    bool is_save_binary = strcmp(argv[3], "savebin") == 0;
    bool is_print = strcmp(argv[3], "print") == 0;
    bool is_count = strcmp(argv[3], "count") == 0;

    if (!is_save_text && !is_save_binary && !is_print && !is_count) {
        fprintf(stderr, "undefined type of action (savetext/savebin/print/count expected)\n");
        return 1;
    }

    if (is_save_text) {
        if (argc < 5) {
            fprintf(stderr, "no save file path\n");
            return 1;
        }
        if (!save_text(&list, argv[4])) {
            fprintf(stderr, "unable to save to file %s", argv[4]);
            return 1;
        }
    } else if (is_save_binary) {
        if (argc < 5) {
            fprintf(stderr, "no save file path\n");
            return 1;
        }
        if (!save_binary(&list, argv[4])) {
            fprintf(stderr, "unable to save to file %s", argv[4]);
            return 1;
        }
    } else if (is_print) {
        if (argc < 5) {
            fprintf(stderr, "no print format string\n");
            return 1;
        }
        apply(&list, print_operation, argv[4]);
        printf("\n");
    } else if (is_count) {
        int count = 0;
        apply(&list, count_operation, &count);
        printf("%d\n", count);
    }

    remove_all_points(&list);

    return 0;
}
