#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void start_exec(void)
{
	char *cmd[3];

	cmd[0] = "ping";
	cmd[1] = "8.8.8.8";
	cmd[2] = NULL;

	printf("HIJO PROC %d\n", getpid());
	execve("/sbin/ping", cmd, NULL);
	perror("exe");
}

int main(void)
{
	pid_t id;
	int status;

	id = fork();
	if (id == 0)
		start_exec();
	printf("PAPA %d\n", getpid());
	while (1)
	{
		printf("proc %d \n", getpid());
		sleep(1);
	}
	waitpid(id, &status, 0);
	return (0);
}

