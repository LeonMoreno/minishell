#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_cmd
{
	char *cmd;
	char **argv;
} t_cmd;

typedef struct s_pipe
{
	int pipe[2];
}	t_pipe;

typedef struct s_sh
{
	int		n_pipe;
	int		n_cmd;
	pid_t	*pid;
	t_pipe	*pipe;
	//int		pipe[2];
	struct	s_cmd	*cmd;
}	t_sh;

void start_child(t_sh *sh, int i)
{
	if (i == 0)
	{
		printf("Soy el hijo  PID = %d\n", getpid());
		close (sh->pipe->pipe[0]);
		dup2(sh->pipe->pipe[1], 1);
		close(sh->pipe->pipe[1]);
		write(1, "Hola..", 6);
	}
	if (i == 1)
	{
		char c[3];
		int fd;

		printf("Soy el hijo  PID = %d\n", getpid());
		fd = open("a", O_CREAT | O_RDWR, 0000644);
		close (sh->pipe->pipe[1]);
		dup2(sh->pipe->pipe[0], 0);
		close(sh->pipe->pipe[0]);
		read(0, &c, 4);
		write(fd, &c, 4);
		printf("%s\n", c);
	}

}	

void start_pipex(t_sh *sh)
{
	int i;

	i = 0;
	sh->pipe = malloc(sizeof(t_pipe) * sh->n_pipe);
	while (sh->n_pipe > i)
	{
		//pipe(sh->pipe);
		pipe(sh->pipe[i].pipe);
		i++;
	}
}

void start_fork(t_sh *sh)
{
	int i;

	i = 0;
	sh->pid = malloc(sizeof(pid_t) * sh->n_cmd);
	while (sh->n_cmd > i)
	{
		sh->pid[i] = fork();
		if (sh->pid[i] == 0)
		{
			start_child(sh, i);
			//start_child(&sh->cmd[i]);
			exit(0);
		}
		i++;
	}
}

void wait_fork(t_sh *sh)
{
	int i;
	int	status;

	i = 0;
	while (i < sh->n_cmd)
	{
		waitpid(sh->pid[i], &status, 0);
		i++;
	}
}

/*void start_cmd(t_sh *sh)
{
	sh->cmd = malloc(sizeof(t_cmd) * sh->n_cmd);
	// Premier cmd
	sh->cmd[0].cmd = malloc(sizeof(char) * 2);
	sh->cmd[0].cmd = "ls";
	sh->cmd[0].argv = malloc(sizeof(char *) * 3);
	sh->cmd[0].argv[0] = malloc(sizeof(char) * 2);
	sh->cmd[0].argv[0] = "ls";
	sh->cmd[0].argv[1] = malloc(sizeof(char) * 3);
	sh->cmd[0].argv[1] = "-ls";
	sh->cmd[0].argv[2] = NULL;
	// 2do cmd
	sh->cmd[1].cmd = malloc(sizeof(char) * 2);
	sh->cmd[1].cmd = "wc";
	sh->cmd[1].argv = malloc(sizeof(char *) * 3);
	sh->cmd[1].argv[0] = malloc(sizeof(char) * 2);
	sh->cmd[1].argv[0] = "wc";
	sh->cmd[1].argv[1] = malloc(sizeof(char) * 3);
	sh->cmd[1].argv[1] = "w";
	sh->cmd[1].argv[2] = NULL;
}*/

int main(void)
{
	t_sh *sh;

	sh = malloc(sizeof(t_sh));
	sh->n_pipe = 1;
	sh->n_cmd = 2;

	printf("**INI PROC %d **\n", getpid());
	//start_cmd(sh);
	start_pipex(sh);
	start_fork(sh);
	wait_fork(sh);
	return (0);
}
