#include "template.h"

#ifndef BUF_SZ
#define BUF_SZ 1024
#endif

int main(int argc, char** argv)
{
	int isA = 0, fd, opt;
	ssize_t numRead;
	char buf[BUF_SZ];

	while((opt = getopt(argc, argv, "a")) != -1)
	{
		isA = 1;
	}
	
	if(optind > 2)
	{
		printf("usage error : option <filename>\n");
		exit(-1);
	}

	fd = DETECT_ERR(open(argv[optind], O_WRONLY | 
							(isA?O_APPEND:O_TRUNC), S_IWUSR|
	S_IRUSR | S_IWGRP | S_IRGRP | S_IWOTH | S_IROTH));
	
	while((numRead = DETECT_ERR(read(STDIN_FILENO, buf, BUF_SZ))) > 0)
	{
		if(DETECT_ERR(write(fd, buf, numRead)) != numRead)
		{
			printf("whole buffer couldn't be written\n");
			exit(-1);
		}

		if(DETECT_ERR(write(STDOUT_FILENO, buf, numRead)) != numRead)
		{
			printf("whole buffer couldn't be written\n");
			exit(-1);
		}
	}

	exit(1);
}

