#include "stego.h"

static char get_id_by_symbol(char symbol) {
    if (symbol == ' ')
        return SPACE_ID;
    else if (symbol == '.')
        return DOT_ID;
    else if (symbol == ',')
        return COMMA_ID;
    else
        return symbol - 'A';
}

static char get_symbol_by_id(char code) {
    if (code == SPACE_ID)
        return ' ';
    else if (code == DOT_ID)
        return '.';
    else if (code == COMMA_ID)
        return ',';
    else
        return 'A' + code;
}

static bool read_key(FILE *stream, KEY *key) {
    return fscanf(stream, "%d %d %c\n", &key->x, &key->y, &key->color) > 0;
}

static void set_bit(BYTE *number, bool val) {
    *number = ((*number >> 1) << 1) | val;
}

static void encode_bit(bool bit, KEY key, BMP *bmp) {
    PIXEL *pixel = &bmp->data[key.y][key.x];
    if (key.color == 'R')
        set_bit(&pixel->red, bit);
    else if (key.color == 'G')
        set_bit(&pixel->green, bit);
    else
        set_bit(&pixel->blue, bit);
}

static bool decode_bit(KEY key, BMP *bmp) {
    PIXEL *pixel = &bmp->data[key.y][key.x];
    if (key.color == 'R')
        return pixel->red & 1;
    else if (key.color == 'G')
        return pixel->green & 1;
    else
        return pixel->blue & 1;
}

void encode_symbol(char symbol, KEY keys[SYMBOL_SIZE], BMP *bmp) {
    char id = get_id_by_symbol(symbol);
    for (int i = 0; i < SYMBOL_SIZE; i++) {
        encode_bit(id >> i & 1, keys[i], bmp);
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
