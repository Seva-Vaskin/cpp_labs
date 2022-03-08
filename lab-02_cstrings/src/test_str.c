#include "test_str.h"

void test_strcpy() {
	char str[20];
	char src[] = "Filatov one love";
	my_strcpy(str, src);
	assert(strcmp(str, src) == 0);
}

void test_strcat() {
	char s1[20] = "test";
	char s2[20] = " to test";
	my_strcat(s1, s2);
	assert(strcmp(s1, "test to test") == 0);
}

void test_strcmp() {
	assert(my_strcmp("abcd", "abc") > 0);
	printf("strcmp test 1 finished\n");
	assert(my_strcmp("abc", "abcd") < 0);
	printf("strcmp test 2 finished\n");
	assert(my_strcmp("I love C", "I love C") == 0);
	printf("strcmp test 3 finished\n");
	assert(my_strcmp("I love Filatov", "I love C") > 0);
	printf("strcmp test 4 finished\n");
}

void test_strlen() {
	assert(my_strlen("12345") == 5);
	assert(my_strlen("") == 0);
}