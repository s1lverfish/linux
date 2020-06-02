#include "../templates/template.h"

int main()
{
	int fd1, fd2;
	off_t off1, off2;

	fd1 = DETECT_ERR(open("in", O_RDONLY));
	fd2 = DETECT_ERR(dup(fd1));

	off1 = DETECT_ERR(lseek(fd1, 12, SEEK_SET));
	off2 = DETECT_ERR(lseek(fd2, 0, SEEK_CUR));

	printf("%ld, %ld\n", off1, off2);

	exit(EXIT_SUCCESS);

}
