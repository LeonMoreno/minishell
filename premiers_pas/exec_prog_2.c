#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int i;

	i = 1;
	printf("%s : %d \n", argv[0], getpid());
	while (i < argc)
	{
		printf("argu %d, %s\n", i, argv[i]);
		i++;
	}
	return (0);
}
