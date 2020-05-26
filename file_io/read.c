#include "template.h"

int main()
{
	printf("page size for my system is: %ld\n", sysconf(_SC_PAGESIZE));
}
