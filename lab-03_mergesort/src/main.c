#include "stdio.h"
#include "mergesort.h"
#include "string.h"
#include "stdlib.h"

int my_strcmp(const void *lhs, const void *rhs) {
	return strcmp(*(const char **)rhs, *(const char **)lhs);
}

int my_intcmp(const void *lhs, const void *rhs) {
	return *((int *)rhs) - *((int *)lhs);
}

int my_charcmp(const void *lhs, const void *rhs) {
	return *((char *)rhs) - *((char *)lhs);
}

int main(int argc, char ** argv) {
	#ifdef DEBUG
		printf("Debug started\n");
	#endif 
	if (argc < 2) {
		printf("Not enough arguments\n");
		return 1;
	}
	size_t elements = argc - 2;
	if (strcmp(argv[1], "int") == 0) {
		#ifdef DEBUG
			printf("int type defiend\n");
		#endif

		int * arr = (int *)malloc(elements * sizeof(int));
		for (size_t i = 0; i < elements; i++) {
			arr[i] = atoi(argv[2 + i]);

			#ifdef DEBUG
				printf("%d found in data\n", arr[i]);
			#endif
		}

		if (mergesort(arr, elements, sizeof(int), my_intcmp) == -1) {
			printf("Error: memory allocation failed.");
			return -1;
		}
		
		
		for (size_t i = 0; i < elements; i++) {
			if (i + 1 < elements) 
				printf("%d ", arr[i]);
			else
				printf("%d\n", arr[i]);
		}
	}
	else if (strcmp(argv[1], "char") == 0) {
		#ifdef DEBUG
			printf("char type defiend\n");
		#endif

		char * arr = (char *)malloc(elements * sizeof(char));
		for (size_t i = 0; i < elements; i++) {
			arr[i] = argv[2 + i][0];

			#ifdef DEBUG
				printf("%c found in data\n", arr[i]);
			#endif
		}
		
		if (mergesort(arr, elements, sizeof(char), my_charcmp) == -1) {
			printf("Error: memory allocation failed.");
			return -1;
		}

		for (size_t i = 0; i < elements; i++) {
			if (i + 1 < elements)
				printf("%c ", arr[i]);
			else
				printf("%c\n", arr[i]);
		}
	}
	else if (strcmp(argv[1], "str") == 0) {
		#ifdef DEBUG
			printf("str type defiend\n");
		#endif

		char ** arr = argv + 2;

		if (mergesort(arr, elements, sizeof (char *), my_strcmp)) {
			printf("Error: memory allocation failed.");
			return -1;
		}		

		#ifdef DEBUG
			printf("Data:\n");
			for (size_t i = 0; i < elements; i++) {
				printf("%s\n", arr[i]);
			}
		#endif

		for (size_t i = 0; i < elements; i++) {
			if (i + 1 < elements)
				printf("%s ", arr[i]);
			else
				printf("%s\n", arr[i]);
		}
	}
	else {
		printf("Undefined type of data\n");
	}
	return 0;
}