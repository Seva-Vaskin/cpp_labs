#include "mergesort.h"

#ifdef DEBUG
size_t mergesort_counter = 0;

void debug_print(const void * data, size_t bytes_count) {
	for (size_t i = 0; i < bytes_count; i++) {
			printf("%c", *((char *)data + i));
		}
}
#endif


int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *)) {
	#ifdef DEBUG
		size_t mergesort_id = mergesort_counter++;
		printf("ID: %ld, data to sort: ", mergesort_id);
		debug_print(array, elements * element_size);
		printf("\n");
	#endif


	if (elements <= 1) {
		#ifdef DEBUG
			printf("Nothing to sort in %ld\n", mergesort_id);
		#endif

		return 0;
	}

	size_t left_elements = elements / 2;
	size_t right_elements = elements - left_elements;
	void * left_arr = array;
	void * right_arr = array + left_elements * element_size;

	if (mergesort(left_arr, left_elements, element_size, comparator) == -1)
		return -1;
	if (mergesort(right_arr, right_elements, element_size, comparator))
		return -1;
	

	void * buf = malloc(elements * element_size);
	if (buf == NULL)
		return -1;

	size_t left_i = 0;
	size_t right_i = 0;
	void * buf_ptr = buf;
	while (left_i < left_elements && right_i < right_elements) {
		if (comparator(left_arr + left_i * element_size, right_arr + right_i * element_size) > 0) {
			memcpy(buf_ptr, left_arr + left_i * element_size, element_size);
			left_i++;
		}
		else {
			memcpy(buf_ptr, right_arr + right_i * element_size, element_size);
			right_i++;
		}
		buf_ptr += element_size;
	}
	while (left_i < left_elements) {
		memcpy(buf_ptr, left_arr + left_i * element_size, element_size);
		left_i++;
		buf_ptr += element_size;
	}
	while(right_i < right_elements) {
		memcpy(buf_ptr, right_arr + right_i * element_size, element_size);
		right_i++;
		buf_ptr += element_size;
	}

	memcpy(array, buf, elements * element_size);
	free(buf);

	#ifdef DEBUG
		printf("%ld finished\nResult data: ", mergesort_id);
		debug_print(array, elements * element_size);
		printf("\n");
	#endif

	return 0;
}