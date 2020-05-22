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


#ifndef BUFFERSIZE
#define BUFFERSIZE 20
#endif

int main(int argc, char** argv)
{
	
	int FD_FROM, FD_TO, openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUFFERSIZE];

	if(argc != 3)
	{
		fprintf(stderr, "usage error: %s <filename>\n", argv[0]);
		exit(1);
	}

	FD_FROM = open(argv[1], O_RDONLY);
	
	DETECT_ERR(FD_FROM);
	
	filePerms = (S_IRUSR | S_IWUSR | S_IRGRP |
			S_IWGRP | S_IROTH | S_IWOTH);

	openFlags = (O_CREAT | O_WRONLY | O_TRUNC);

	FD_TO = open(argv[2], openFlags, filePerms);

	DETECT_ERR(FD_TO);
	
	while((numRead = read(FD_FROM, buf, BUFFERSIZE)) > 0);
	{
		//printf("%ld %s", numRead, buf);
		if(write(FD_TO, buf, numRead) != numRead)
		{
			fprintf(stderr, "couldn't write whole buffer\n");
			exit(-1);
		}
	}


	DETECT_ERR(numRead);
	
	DETECT_ERR(close(FD_FROM));
	DETECT_ERR(close(FD_TO));

	exit(EXIT_SUCCESS);
}
