#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv)
{
	int option;
	while((option = getopt(argc, argv, "cf")) != -1)
	{
		switch(option)
		{
			case 'c': 
					printf("normal temperature\n");
					break;
			case 'f':
					printf("ok boomer\n");
					break;
			default:
					printf("error\n");
					exit(2);		
		}
	}
}
