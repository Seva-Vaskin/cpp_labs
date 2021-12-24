#include "stego.h"

char get_id_by_symbol(char symbol) {
    if (symbol == ' ')
        return 26;
    else if (symbol == '.')
        return 27;
    else if (symbol == ',')
        return 28;
    else
        return symbol - 'A';
}

char get_symbol_by_id(char code) {
    if (code == 26)
        return ' ';
    else if (code == 27)
        return '.';
    else if (code == 28)
        return ',';
    else
        return 'A' + code;
}

bool read_key(FILE *stream, KEY *key) {
    return fscanf(stream, "%d %d %c\n", &key->x, &key->y, &key->color) > 0;
}

void write_key(FILE *stream, KEY key) {
    fprintf(stream, "%d %d %c\n", key.x, key.y, key.color);
}

void encode_bit(bool bit, KEY key, BMP *bmp) {
    fprintf(stderr, "%d", bit);
    PIXEL *pixel = &bmp->data[key.y][key.x];
    if (key.color == 'R')
        set_bit(&pixel->red, bit);
    else if (key.color == 'G')
        set_bit(&pixel->green, bit);
    else
        set_bit(&pixel->blue, bit);
}


bool decode_bit(KEY key, BMP *bmp) {
    PIXEL *pixel = &bmp->data[key.y][key.x];
    if (key.color == 'R')
        return pixel->red & 1;
    else if (key.color == 'G')
        return pixel->green & 1;
    else
        return pixel->blue & 1;
}

void set_bit(BYTE *number, bool val) {
    *number = ((*number >> 1) << 1) | val;
}

void encode_symbol(char symbol, KEY keys[SYMBOL_SIZE], BMP *bmp) {
    char id = get_id_by_symbol(symbol);
    for (int i = 0; i < SYMBOL_SIZE; i++, id >>= 1) {
        encode_bit(id & 1, keys[i], bmp);
    }
}

char decode_symbol(KEY keys[SYMBOL_SIZE], BMP *bmp) {
    char id = 0;
    for (int i = 0; i < SYMBOL_SIZE; i++) {
        id |= decode_bit(keys[i], bmp) << i;
    }
    return get_symbol_by_id(id);
}

bool read_keys(KEY keys[SYMBOL_SIZE], FILE *stream) {
    bool ans = true;
    for (int i = 0; i < SYMBOL_SIZE && ans; i++) {
        ans &= read_key(stream, &keys[i]);
    }
    return ans;
}

void write_keys(KEY keys[SYMBOL_SIZE], FILE *stream) {
    for (int i = 0; i < SYMBOL_SIZE; i++) {
        write_key(stream, keys[i]);
    }
}

KEY make_key(int *x, int *y, BMP *bmp) {
    (*x)++;
    if (*x == bmp->bit_map_info.bi_width) {
        *x = 0;
        y++;
    }
    KEY result;
    result.x = *x;
    result.y = *y;
    result.color = 'R';
    return result;
}

void make_keys(int *x, int *y, BMP *bmp, KEY keys[SYMBOL_SIZE]) {
    for (int i = 0; i < SYMBOL_SIZE; i++) {
        keys[i] = make_key(x, y, bmp);
    }
}
