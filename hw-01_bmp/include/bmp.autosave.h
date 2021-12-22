#ifndef BMP_H
#define BMP_H value

#include <>

typedef char BYTE;
typedef short WORD;
typedef unsigned int DWORD;
typedef int LONG;

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
	DWORD red;
	DWORD green;
	DWORD blue;

} PIXEL;

typedef struct
{
	BIT_MAP_FILE_HEADER bit_map_file_header;
	BIT_MAP_INFO bit_map_info;
	PIXEL *flat_data;
	PIXEL **data;
} BMP;

void read_BMP(BMP *bmp, FILE *stream);

#ifdef DEBUG
#define d_print_BIT_MAP_INFO(__a) printf("BIT_MAP_INFO:\n \
										size: %d\n \
											width: %d\n \
											height: %d\n \
											planes: %d\n \
											bit_count: %d\n \
											compression: %d\n \
											size_image: %d\n \
											x_pels_per_meter: %d\n \
											y_pels_per_meter: %d\n \
											clr_used: %d\n \
											crl_inortant: %d\n", \
											(__a).bi_size, \
											(__a).bi_width, \
											(__a).bi_height, \
											(__a).bi_planes, \
											(__a).bi_bit_count, \
											(__a).bi_compression, \
											(__a).bi_size_image, \
											(__a).bi_x_pels_per_meter, \
											(__a).bi_y_pels_per_meter, \
											(__a).bi_clr_used, \
											(__a).bi_clr_important)
#else
#define d_print_BIT_MAP_INFO(__a)
#endif

#ifdef DEBUG
#define d_print_BIT_FILE_HEADER(__a) printf("BIT_FILE_HEADER:\n \
											type: %d\n \
											size: %d\n \
											reserved_1: %d\n \
											reserved_2: %d\n \
											off_bits: %d\n", \
											(__a).bf_type, \
											(__a).bf_size, \
											(__a).bf_reserved_1, \
											(__a).bf_reserved_2, \
											(__a).bf_off_bits)
#else
#define d_print_BIT_FILE_HEADER(__a)
#endif

#endif