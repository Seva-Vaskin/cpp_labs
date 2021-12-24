#ifndef STEGO_H
#define STEGO_H

#include "bmp.h"
#include <stdbool.h>
#include <stdio.h>
#

#define SYMBOL_SIZE 5

typedef struct {
    LONG x;
    LONG y;
    char color;
} KEY;

bool read_key(FILE *stream, KEY *key);

bool read_keys(KEY keys[SYMBOL_SIZE], FILE *stream);

void write_key(FILE *stream, KEY key);

char get_id_by_symbol(char symbol);

char get_symbol_by_id(char code);

void set_bit(BYTE *number, bool val);

void encode_bit(bool bit, KEY key, BMP *bmp);

bool decode_bit(KEY key, BMP *bmp);

void encode_symbol(char symbol, KEY keys[SYMBOL_SIZE], BMP *bmp);

char decode_symbol(KEY keys[SYMBOL_SIZE], BMP *bmp);

void write_keys(KEY keys[SYMBOL_SIZE], FILE *stream);

KEY make_key(int *x, int *y, BMP *bmp);

void make_keys(int *x, int *y, BMP *bmp, KEY keys[SYMBOL_SIZE]);

#endif