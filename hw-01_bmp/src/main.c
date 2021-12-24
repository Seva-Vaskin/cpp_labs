#include <stdio.h>
#include <string.h>

#include "bmp.h"
#include "stego.h"

BMP *read_bmp(char *filename) {
    FILE *input_stream = fopen(filename, "rb");
    if (!input_stream) {
        fprintf(stderr, "can't open input file\n");
        return NULL;
    }
    BMP *bmp = (BMP *) malloc(sizeof(BMP));
    if (!bmp) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }
    load_bmp(bmp, input_stream);
    fclose(input_stream);
    return bmp;
}

int write_bmp(BMP *bmp, char *filename) {
    FILE *output_stream = fopen(filename, "wb");
    if (!output_stream) {
        fprintf(stderr, "can't open output file\n");
        return 1;
    }
    save_bmp(bmp, output_stream);
    fclose(output_stream);
    return 0;
}

int crop_rotate(int argc, char *argv[]) {
    if (argc < 8) {
        fprintf(stderr, "Not enough arguments\n");
        return 1;
    }

    BMP *bmp = read_bmp(argv[2]);
    if (!bmp)
        return 1;

    LONG x = atoi(argv[4]);
    LONG y = atoi(argv[5]);
    LONG w = atoi(argv[6]);
    LONG h = atoi(argv[7]);

    BMP *cropped_bmp = crop(bmp, x, y, w, h);
    if (!cropped_bmp) {
        free_bmp(bmp);
        fprintf(stderr, "Error while cropping bmp\n");
        return 1;
    }

    BMP *cropped_rotated_bmp = rotate(cropped_bmp);
    if (!cropped_rotated_bmp) {
        free_bmp(bmp);
        free_bmp(cropped_bmp);
        fprintf(stderr, "Error while rotating bmp\n");
        return 1;
    }

    int exit_code = write_bmp(cropped_rotated_bmp, argv[3]);
    free_bmp(bmp);
    free_bmp(cropped_bmp);
    free_bmp(cropped_rotated_bmp);
    return exit_code;
}

int make_copy(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Not enough arguments\n");
        return 1;
    }

    BMP *bmp = read_bmp(argv[2]);
    if (!bmp)
        return 1;

    LONG x = 0;
    LONG y = 0;
    LONG w = bmp->bit_map_info.bi_width;
    LONG h = bmp->bit_map_info.bi_height;

    BMP *cropped_bmp = crop(bmp, x, y, w, h);
    if (!cropped_bmp) {
        fprintf(stderr, "Error while cropping bmp\n");
        return 1;
    }

    int exit_code = write_bmp(cropped_bmp, argv[3]);
    free_bmp(bmp);
    free_bmp(cropped_bmp);
    return exit_code;
}

int insert(int argc, char *argv[]) {
    if (argc < 6) {
        fprintf(stderr, "Not enough arguments\n");
        return 1;
    }

    BMP *bmp = read_bmp(argv[2]);
    if (!bmp) {
        fprintf(stderr, "can't read input bmp file");
        return 1;
    }

    FILE *key_stream  = fopen(argv[4], "w");
    if (!key_stream) {
        fprintf(stderr, "can't open key file\n");
        return 1;
    }
    FILE *message_stream = fopen(argv[5], "r");
    if (!message_stream) {
        fprintf(stderr, "can't open message file\n");
        return 1;
    }


    char c;
    KEY keys[SYMBOL_SIZE];
    int x = 0, y = 0;
    while ((c = getc(message_stream)) != EOF) {
        make_keys(&x, &y, bmp, keys);
        write_keys(keys, key_stream);
        encode_symbol(c, keys, bmp);
    }

    fclose(key_stream);
    fclose(message_stream);
    if (write_bmp(bmp, argv[3]) != 0) {
        fprintf(stderr, "Error while writing result file\n");
        return 1;
    }
    return 0;
}

int extract(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Not enough arguments\n");
        return 1;
    }

    BMP *bmp = read_bmp(argv[2]);
    if (!bmp) {
        fprintf(stderr, "can't read input bmp file");
        return 1;
    }

    FILE *key_stream = fopen(argv[3], "r");
    if (!key_stream) {
        fprintf(stderr, "can't open key file\n");
        return 1;
    }
    FILE *message_stream = fopen(argv[4], "w");
    if (!message_stream) {
        fprintf(stderr, "can't open message file\n");
        return 1;
    }


    KEY keys[SYMBOL_SIZE];
    while (read_keys(keys, key_stream)) {
        char c = decode_symbol(keys, bmp);
        fprintf(message_stream, "%c", c);
    }

    fclose(key_stream);
    fclose(message_stream);
    return 0;
}

int process_operation(int argc, char *argv[], int (*operation)(int, char **)) {
    int exit_code = operation(argc, argv);
    if (exit_code == 0) {
        fprintf(stderr, "operation succeed\n");
        return 0;
    } else {
        fprintf(stderr, "operation failed\n");
        return 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Not enough arguments\n");
        return 1;
    }
    if (strcmp(argv[1], "make-copy") == 0) { // this operation added for debug
        fprintf(stderr, "make-copy operation defined\n");
        return process_operation(argc, argv, make_copy);
    } else if (strcmp(argv[1], "crop-rotate") == 0) {
        fprintf(stderr, "crop-rotate operation defined\n");
        return process_operation(argc, argv, crop_rotate);
    } else if (strcmp(argv[1], "insert") == 0) {
        fprintf(stderr, "insert operation defined\n");
        return process_operation(argc, argv, insert);
    } else if (strcmp(argv[1], "extract") == 0) {
        fprintf(stderr, "extract operation defined\n");
        return process_operation(argc, argv, extract);
    } else {
        fprintf(stderr, "Undefined operation type\n");
        return 1;
    }
}