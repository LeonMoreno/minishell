#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int fd;
	int tty;
	char *name;

	//fd = open("ens.txt", O_NOCTTY);
	fd = open("/dev/ttyp0", O_RDONLY);

	printf("fd = %d\n", fd);
	
	tty = isatty(fd);
	name = ttyname(fd);
	perror("ERR");

	printf("tty = %d, %s\n", tty, name);
	
	return (0);
}
