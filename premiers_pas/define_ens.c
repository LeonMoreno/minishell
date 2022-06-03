#include <stdio.h>
#include <string.h>

#define CMD "cmd"
#define CMD	"env" 

int main(void)
{
	char *str = "cmd";

	if (!strcmp(CMD, str))
		printf("str = %s\n", str);
	return (0);
}
