#include "str.h"

char* my_strcpy(char *restrict dest, const char *restrict src) {
	char * retPtr = dest;
	while (*(dest++) = *(src++));
	return retPtr;
}

char* my_strcat(char *restrict dest, const char *restrict src) {
	char * retPtr = dest;
	while (*(dest++));
	my_strcpy(dest - 1, src);
	return retPtr;
}

int my_strcmp(const char *lhs, const char *rhs) {
	while (*lhs && *rhs && *lhs == *rhs) {
		lhs++;
		rhs++;
	}
	return *lhs - *rhs;
}

size_t my_strlen(const char *str) {
	char *ptr = (char *)str;
	while (*(ptr++));
	return ptr - 1 - str;
}