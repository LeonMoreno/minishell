#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_exec_child(int *pipe_fds, char **env, int *w_fd)
{
	char *argvec[2];
	char tab[] = "cat";
	int new_parent;

	argvec[0] = tab;
	argvec[1] = NULL;
	dup2(w_fd[0], 0);
	close (w_fd[1]);
	//printf("I'm a child %d\n", getpid());
	close(pipe_fds[0]);
	new_parent = fork();
	if (!new_parent)
	{
		new_parent = open("a", O_WRONLY | O_CREAT, 0777);
		dup2(new_parent, STDOUT_FILENO);
		execve("/bin/cat", argvec, env);
		exit(0);
	}
	dup2(pipe_fds[1], STDOUT_FILENO);
	execve("/bin/cat", argvec, env);
	exit(0);
}

int main (int argc, char **argv, char **env)
{
	int fd[2];
	int w_fd[2];
	int me;
	char str[1000];
	(void) argc;
	(void) argv;
	
	pipe(fd);
	me = fork();
	pipe(w_fd);
	write (w_fd[1], "HEILLO LÀ LÀ\n", 20);
	if (!me)
	{
		//printf("I'm a child %d\n", getpid());
		ft_exec_child(fd, env, w_fd);		
	}
	else
		printf("I'm an adult %d\n", getpid());

	read(fd[0], str, 1000);
	close (fd[0]);
	close (fd[1]);
	close (w_fd[0]);
	close (w_fd[1]);
	wait(NULL);
	printf("I'm still here %d\nAnd i have this to say : %s\n", getpid(), str);
}
