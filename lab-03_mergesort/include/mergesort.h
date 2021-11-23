#ifndef MERGESORT_H
#define MERGESORT_H

#include "stdlib.h"
#include "stddef.h"
#include "assert.h"

#ifdef DEBUG
#include "stdio.h"
#endif

void my_memcpy(void *dst, const void *src, size_t bytes_count);

int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *));

#endif