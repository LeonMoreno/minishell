#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int i;
	char *argv2[] = {"prog2", "hola", "leo", NULL};

	i = 1;
	printf("%s : %d \n", argv[0], getpid());
	execve("./prog2", argv2, NULL);
	return (0);
}


