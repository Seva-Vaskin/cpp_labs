#ifndef STR_H
#define STR_H

#include "stddef.h"

char* my_strcpy(char *restrict dest, const char *restrict src);

char* my_strcat(char *restrict dest, const char *restrict src);

int my_strcmp(const char *lhs, const char *rhs);

size_t my_strlen(const char *str);

#endif