#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>


#define DETECT_ERR(X) ({long __val = (long)(X); (__val == -1 ? \
						({fprintf(stderr,"ERROR ("__FILE__":%d) -- %s\n" \
						, __LINE__, strerror(errno)); \
						exit(-1);-1;}) : __val); })

int main(int argc, char **argv)
{
	off_t offset;
	int fd, i, j;
	size_t len;
	char *buf;
	ssize_t numRead, numWritten;
	
	if(argc < 3)
	{
		printf("usage error: <filename> <action><times>\n");
		exit(-1);
	}

	fd = DETECT_ERR(open(argv[1], O_RDWR| O_CREAT , 
							S_IRUSR | S_IWUSR | 
							S_IRGRP | S_IWGRP | 
							S_IROTH | S_IWOTH));

	for(i = 2; i < argc; i++)
	{
		switch(argv[i][0]) {

		case 'r':
		case 'R':
		
		len = DETECT_ERR(atoi(&argv[i][1]));
		printf("%ld\n", len);	
		buf = malloc(len+1);
		if(buf == NULL) 
		{
			printf("malloc error\n");
			exit(-1);
		}
		numRead = DETECT_ERR(read(fd, buf, len));
		printf("%ld\n", numRead);
		if(numRead == 0)
		{
			printf("%s : <end-of-file>\n", argv[i]);
		}else
		{
			printf("%s : ", argv[i]);
			for(j = 0; j < numRead; j++)
			{
				if(argv[i][0] == 'r')
				{
					printf("%c ", (isprint((unsigned char)buf[j]) ?
									buf[j] : '?'));
				}else
				{
					printf("%02x ", (unsigned char)buf[j]);

				}
			}
			printf("\n");
		}
		
		free(buf);
		break;
		
		case 'w':

		numWritten = DETECT_ERR(write(fd, &argv[i][1], strlen(&argv[i][1])));

		printf("%s: wrote %ld bytes \n", argv[i], numWritten);
		break;

		case 's':

		offset = (off_t)DETECT_ERR(atoi(&argv[i][1]));
		
		DETECT_ERR(lseek(fd, offset, SEEK_SET));

		printf("%s: seek succeeded\n", argv[i]);
		break;

		default: printf("Argument must start with [rRws]: %s\n", argv[i]);
		}
	}
	
	exit(1);
}
