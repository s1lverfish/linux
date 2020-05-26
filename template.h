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
