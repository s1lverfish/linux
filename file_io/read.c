#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#define DETECT_ERR(X) ({long __val = (long)(X); (__val == -1 ? \
						({fprintf(stderr,"ERROR ("__FILE__":%d) -- %s\n" \
						, __LINE__, strerror(errno)); \
						exit(-1);-1;}) : __val); })

#define BUF_SIZE 20
char buf[BUF_SIZE];

int main()
{
	ssize_t numRead;

	int fd = open("in", O_RDONLY);

	while(1)
	{
		numRead = DETECT_ERR(read(fd, buf, BUF_SIZE));
		if(numRead > 0)
			printf("%ld \n", write(STDOUT_FILENO, buf, numRead));
		else break;
	}
}
