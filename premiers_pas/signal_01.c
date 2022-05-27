#include <stdio.h>
#include <signal.h>

void ctrl(int sig_num)
{
	//signal(SIGINT, ctrl);
	printf("\n Oprimi ctrl + c\n");
}

int main(void)
{
	printf("Hola este es un ensayo\n");
	signal(SIGINT, ctrl);
	while (1)
	{
	}
	return (0);
}
