#include "../templates/template.h"

int main(int argc, char** argv)
{
	int fd;	
	size_t written;
	char buf[] = "hello world";

	fd = DETECT_ERR(open("in", O_WRONLY));
	
	DETECT_ERR(lseek(fd, 12, SEEK_SET));
	
	written = DETECT_ERR(write(fd, buf, strlen(buf)*sizeof(char)));

	if(written != strlen(buf)*sizeof(char))
	{
		printf("could'nt write whole buffer");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
