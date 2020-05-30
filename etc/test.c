#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

struct person
{
	char* name;
	int height;
};

char* ar[10];

char arr[10];
int main(int argc, char* argv[])
{
/*		
	if(args > 1)
		for(int i = 1; i < args; i++)
			printf("%s is a number\n", argv[i]);	
	
	system("echo DONE!");
	
	char **ptr;

	ptr = (char**)calloc(10, sizeof(char*));
	
	ptr[0] = (char*)malloc(10*sizeof(char));

	ptr[0][0] = 'a';
	ptr[0][1] = 'b';

	char* const str = (char* const)malloc(10*sizeof(char));	
	
	strcpy(str, "one two"); 

	printf("%s %s\n",ptr[0], str); 


	struct stat myStruct;
	printf("%ld\n", sizeof(struct stat));
*/
	arr[10] = 's';
	ar[10] = arr;
	printf("%p, %p, %c\n", argv[argc], ar[10], (arr[10] == '\0' ? 'y' : 'n'));
	printf("%ld\n", sysconf(_SC_ARG_MAX));
	return 0;
}
