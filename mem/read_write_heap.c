#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>



#define DETECT_ERR(X) ({int __val = (long)(X); (__val == -1 ? \
						({fprintf(stderr,"ERROR ("__FILE__":%d) -- %s\n" \
						, __LINE__, strerror(errno)); \
						exit(-1);-1;}) : __val); })

int main(int argc, char **argv)
{
	
	char *curStr = strdup(argv[2]);
	char *newStr = strdup(argv[3]);
	int memfd;
	FILE* mapfd;

	char memPath[25]; 
	char mapPath[25];
	DETECT_ERR(sprintf(memPath, "/proc/%s/mem", argv[1]));
	DETECT_ERR(sprintf(mapPath, "/proc/%s/maps", argv[1]));
	
	memfd =	DETECT_ERR(open(memPath, O_RDWR));
	mapfd = fopen(mapPath, "r");
	if(mapfd == NULL) { printf("error opening %s\n", mapPath); exit(-1); }
	
	size_t lineLen = 0;
	char* line = NULL;
	ssize_t wordsRead;
	int found = 0;
	char *cur;

	while ((wordsRead = getline(&line, &lineLen, mapfd)) != -1) {
		cur = strtok(line, " ");
		while(cur != NULL)
		{
			int diff = strcmp(cur, "[heap]");
			if(diff == 10) { /*printf("%s, %d\n", cur, strcmp(cur, "[heap]"));*/ found = 1; break; }
			cur = strtok(NULL, " ");
		}
		if(found) break;
	}
	cur = strtok(line, " ");
	char *block = cur;

	printf("memory block: %s\n", block);
	
	cur = strtok(block, "-");
	long int start = ( long int)strtol(cur, NULL, 16);
	cur = strtok(NULL, "-");
	long int end = ( long int)strtol(cur, NULL, 16);
	
	printf("%lX, %lX\n", start, end);

	char *buf = (char*)malloc(end-start);

	ssize_t numRead = pread(memfd, buf, end-start, (off_t)start);
	/*
	printf("%ld, %ld\n", numRead, end-start);
	if(numRead - end-start != 0);
	{
		printf("couldn't read whole buffer\n"); 
		exit(-1);
	}
	*/
	int len = strlen(curStr);
	char *subStr = (char*)malloc(sizeof(char)*len);
	int loc, ok = 0;
	for(int i = 0; i < (end-start)-len; i++)
	{
		subStr = strncpy(subStr, buf+i, len); 
		int cmp = strcmp(subStr, curStr);
		if(cmp == 0)
		{
			loc = i;
			break;
		}
		
		//printf(" %d, %d, %s\n", cmp, i, subStr);
	}
	
/*
	char *pos = strstr(buf, curStr);
	if(pos == NULL) exit(-1);	
	printf("%ld\n", pos-buf);
*/
	len = strlen(newStr);
	pwrite(memfd, newStr, len*sizeof(char), start+loc);

}	

