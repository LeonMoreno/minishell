#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *cmd[3];

	cmd[0]  = "ping";
	cmd[1]	= "8.8.8.8";
	cmd[2]  = NULL;

	printf("*** PROC INICIAL PID %d\n", getpid());
	execve("/sbin/ping", cmd, NULL);
	printf("algo aqui\n");
	perror("exe");
	return (0);
}
