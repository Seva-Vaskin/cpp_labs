#include "stdio.h"
#include "test_str.h"

int main(int argc, char const *argv[])
{
	test_strcmp();
	printf("strcmp tested \n");
	test_strcpy();
	printf("strcpy tested \n");
	test_strcat();
	printf("strcat tested \n");
	test_strlen();
	printf("strlen tested \n");
	printf("All tests finished \n");	
	return 0;
}