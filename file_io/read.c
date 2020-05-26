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

struct buf {
	char first;
	char second[10];
	char third;
	int num;
};

int main()
{
	ssize_t numRead;

	int fd = open("in", O_RDONLY);

	struct buf myBuf;

	printf("%ld\n", sizeof(struct buf));

	numRead = DETECT_ERR(read(fd, &myBuf, sizeof(struct buf)));
	
	printf("%ld, %c, %s, %c, %d\n", numRead, myBuf.first, myBuf.second, myBuf.third, myBuf.num); 
}
