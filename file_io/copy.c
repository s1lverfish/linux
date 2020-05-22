#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUFFERSIZE
#define BUFFERSIZE 1024
#endif
int main(int argc, char** argv)
{
	
	int FD_FROM, FD_TO;
	
	if(argc != 3)
	{
		printf("usage error <filename>\n");
		exit(1);
	}
	
	FD_FROM = open(argv[1], O_RDONLY);

	if(FD_FROM == -1)
	{
		char *error_msg = (char*)malloc(20*sizeof(char));
		sprintf(error_msg, "errno %d", errno);
		printf("opening file %s\n", argv[1]);
		system(error_msg);
		exit(1);
	}
	

	return 0;
}
