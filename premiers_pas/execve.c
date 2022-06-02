#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *cmd[4];

	cmd[0]  = "ls";
	cmd[1]	= "-l";
	cmd[2]	= "*";
	cmd[3]  = NULL;

	printf("*** PROC INICIAL PID %d\n", getpid());
	execve("/bin/ls", cmd, NULL);
	printf("algo aqui\n");
	perror("exe");
	return (0);
}
