#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char *s;// = (char*)malloc(11*sizeof(char));
	unsigned long i = 0;

	s = strdup("helloworld");

	while(s)
	{
		printf("[%ld] %s (%p)\n", i, s, (void*)s);
		sleep(2);
		i++;
	}
}
