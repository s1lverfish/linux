#include <template.h>

extern char** environ;

int my_unsetenv(const char* name)
{
	int exists = 1;
	if(getenv(name) == NULL) exists = 1;
	char* str = malloc(strlen(name)*sizeof(char));

	strcpy(str, name);
	if(exists) putenv(str);

	return 0;
}

int my_setenv(const char* name, const char* value, int overwrite)
{
	int exists = 1;
	if(getenv(name) == NULL) exists = 0;

	if(exists && !overwrite) return -1;

		if(exists) DETECT_ERR(my_unsetenv(name));
		char* string = malloc((strlen(name)+1+strlen(value))*sizeof(char));
		strcpy(string, name);
		string[strlen(name)] = '=';
		strcpy(string+strlen(name)+1, value);
		putenv(string);

	return 0;
}


int main(int argc, char** argv)
{

	system("printenv | grep MYVAR");
	my_setenv("MYVAR", "hello", 0);
	system("printenv | grep MYVAR");
	my_setenv("MYVAR", "new_name", 0);
	system("printenv | grep MYVAR");
	my_setenv("MYVAR", "new_name", 1);
	system("printenv | grep MYVAR");
	my_unsetenv("MYVAR");
	system("printenv | grep MYVAR");


	exit(EXIT_SUCCESS);
}


