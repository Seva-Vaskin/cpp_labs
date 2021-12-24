#ifndef STEGO_H
#define STEGO_H

#include "bmp.h"
#include <stdbool.h>
#include <stdio.h>
#

#define SYMBOL_SIZE 5
#define SPACE_ID 26
#define DOT_ID 27
#define COMMA_ID 28

typedef struct {
    LONG x;
    LONG y;
    char color;
} KEY;

bool read_keys(KEY keys[SYMBOL_SIZE], FILE *stream);

void encode_symbol(char symbol, KEY keys[SYMBOL_SIZE], BMP *bmp);

char decode_symbol(KEY keys[SYMBOL_SIZE], BMP *bmp);

#endif