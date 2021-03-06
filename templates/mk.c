#include <stdio.h>
#include <stdlib.h>

#ifndef BUF_SZ
#define BUF_SZ 100
#endif

char buf[BUF_SZ];

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("Wrong number of args\n Format: file.cpp outfile\n");
		exit(0);
	}
	int n = sprintf(buf, "cc %s ~/cc/templates/template.c ~/cc/templates/template.h -Wall -o %s", argv[1], argv[2]);

	system(buf);
	exit(1);
}
