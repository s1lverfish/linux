#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>



#define DETECT_ERR(X) ({long __val = (long)(X); (__val == -1 ? \
						({fprintf(stderr,"ERROR ("__FILE__":%d) -- %s\n" \
						, __LINE__, strerror(errno)); \
						exit(-1);-1;}) : __val); })


#ifndef BUFF_SIZE
#define BUFF_SIZE 1024
#endif

int main(int argc, char** argv)
{
	
	int inputFd, outputFd, openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUFF_SIZE];

	if(argc != 3)
	{
		fprintf(stderr, "usage error: %s <filename>\n", argv[0]);
		exit(-1);
	}

	inputFd = DETECT_ERR(open(argv[1], O_RDONLY));
	
	filePerms = (S_IRUSR | S_IWUSR | S_IRGRP |
			S_IWGRP | S_IROTH | S_IWOTH);

	openFlags = (O_CREAT | O_WRONLY | O_TRUNC);

	outputFd = DETECT_ERR(open(argv[2], openFlags, filePerms));
	
	while(numRead = DETECT_ERR(read(inputFd, buf, BUFF_SIZE)), numRead > 0)
		if(write(outputFd, buf, numRead) != numRead)
		{
			fprintf(stderr, "couldn't write whole buffer\n");
			exit(-1);
		}
	
	DETECT_ERR(close(inputFd));
	DETECT_ERR(close(outputFd));

	exit(EXIT_SUCCESS);
}
