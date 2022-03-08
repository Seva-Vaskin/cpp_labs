#include "bmp.h"

static LONG get_padding_size(LONG row_length) {
    return (PADDING_ALIGNMENT - row_length * sizeof(PIXEL) % PADDING_ALIGNMENT) % PADDING_ALIGNMENT;
}

static LONG get_row_byte_length(LONG row_length) {
    return row_length * sizeof(PIXEL) + get_padding_size(row_length);
}

static void init_data(BMP *bmp) {
    bmp->data = (PIXEL **) malloc(bmp->bit_map_info.bi_height * sizeof(PIXEL *));
    LONG row_byte_length = get_row_byte_length(bmp->bit_map_info.bi_width);
    for (int i = 0; i < bmp->bit_map_info.bi_height; i++) {
        bmp->data[bmp->bit_map_info.bi_height - 1 - i] = (PIXEL *) (bmp->flat_data + i * row_byte_length);
    }
}

static bool check_bmp_subrectangular(BMP *bmp, LONG x, LONG y, LONG w, LONG h) {
    return 0 <= x && 0 < w
           && 0 <= y && 0 < h
           && x + w <= bmp->bit_map_info.bi_width
           && y + h <= bmp->bit_map_info.bi_height;
}

void load_bmp(BMP *bmp, FILE *stream) {
    // header reading
    fread(&bmp->bit_map_file_header, sizeof(BIT_MAP_FILE_HEADER), 1, stream);
    fread(&bmp->bit_map_info, sizeof(BIT_MAP_INFO), 1, stream);

    // data reading
    bmp->flat_data = (char *) malloc(bmp->bit_map_info.bi_size_image);
    fread(bmp->flat_data, bmp->bit_map_info.bi_size_image, 1, stream);
    init_data(bmp);
}

void free_bmp(BMP *bmp) {
    free(bmp->flat_data);
    free(bmp->data);
    free(bmp);
}

BMP *create_bmp(BMP *header_src, int w, int h) {
    BMP *result = (BMP *) malloc(sizeof(BMP));
    *result = *header_src;
    DWORD image_size = h * get_row_byte_length(w);
    result->bit_map_file_header.bf_size = image_size + sizeof(BIT_MAP_FILE_HEADER) + sizeof(BIT_MAP_INFO);
    result->bit_map_info.bi_height = h;
    result->bit_map_info.bi_width = w;
    result->bit_map_info.bi_size_image = image_size;
    result->flat_data = (char *) calloc(image_size, 1);
    init_data(result);
    return result;
}

void save_bmp(BMP *bmp, FILE *stream) {
    fwrite(&bmp->bit_map_file_header, sizeof(BIT_MAP_FILE_HEADER), 1, stream);
    fwrite(&bmp->bit_map_info, sizeof(BIT_MAP_INFO), 1, stream);
    fwrite(bmp->flat_data, 1, bmp->bit_map_info.bi_size_image, stream);
}

BMP *crop(BMP *bmp, LONG x, LONG y, LONG w, LONG h) {
    if (!check_bmp_subrectangular(bmp, x, y, w, h))
        return NULL;
    BMP *result = create_bmp(bmp, w, h);
    for (LONG i = 0; i < h; i++) {
        for (LONG j = 0; j < w; j++) {
            result->data[i][j] = bmp->data[y + i][x + j];
        }
    }
    return result;
}

BMP *rotate(BMP *bmp) {
    LONG w = bmp->bit_map_info.bi_width;
    LONG h = bmp->bit_map_info.bi_height;
    BMP *result = create_bmp(bmp, h, w);
    for (LONG i = 0; i < h; i++) {
        for (LONG j = 0; j < w; j++) {
            result->data[j][h - 1 - i] = bmp->data[i][j];
        }
    }
    return result;
}
