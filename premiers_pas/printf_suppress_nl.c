#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char c;

	c = 'a';
	write(1, &c, 2);
	//printf("HOla\n");
	//c = '\n';
	//write(1, &c, 1);
	return (0);
}
