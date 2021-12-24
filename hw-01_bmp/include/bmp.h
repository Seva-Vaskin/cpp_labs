#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char BYTE;
typedef short WORD;
typedef unsigned int DWORD;
typedef int LONG;

#define PADDING_ALIGNMENT 4

typedef struct
{
    WORD bf_type;
    DWORD bf_size;
    WORD bf_reserved_1;
    WORD bf_reserved_2;
    DWORD bf_off_bits;

} __attribute__((packed)) BIT_MAP_FILE_HEADER;

typedef struct
{
    DWORD bi_size;
    LONG bi_width;
    LONG bi_height;
    WORD bi_planes;
    WORD bi_bit_count;
    DWORD bi_compression;
    DWORD bi_size_image;
    LONG bi_x_pels_per_meter;
    LONG bi_y_pels_per_meter;
    DWORD bi_clr_used;
    DWORD bi_clr_important;

} __attribute__((packed)) BIT_MAP_INFO;


typedef struct {
    BYTE blue;
    BYTE green;
    BYTE red;

} PIXEL;

typedef struct
{
    BIT_MAP_FILE_HEADER bit_map_file_header;
    BIT_MAP_INFO bit_map_info;
    PIXEL *flat_data;
    PIXEL **data;

} BMP;

void init_data(BMP *bmp);

void load_bmp(BMP *bmp, FILE *stream);

void save_bmp(BMP *bmp, FILE *stream);

BMP* create_bmp(BMP* header_src, int h, int w);

BMP* crop(BMP *bmp, LONG x, LONG y, LONG w, LONG h);

BMP* rotate(BMP *bmp);

void free_bmp(BMP *bmp);

LONG get_padding_size(LONG row_length);

LONG get_row_byte_length(LONG row_length);

bool check_bmp_subrectangular(BMP *bmp, LONG x, LONG y, LONG w, LONG h);

#endif