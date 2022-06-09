#include "minishell.h"

void	start_child_builtins(t_cmd *cm, t_sh *sh)
{
	int i;

	i = sh->m_pipe;
	printf("EXE CMD builtins %s PID %d\n", cm->name, getpid());
	close(sh->pipe[i].p[OUT]);
	dup2(sh->pipe[i].p[IN], STDOUT_FILENO);
	close(sh->pipe[i].p[IN]);
	start_builtins(cm, sh);
	exit (0);
}

void	start_child_cmdext(t_cmd *cm, t_sh *sh, int x)
{
	char *path;
	//int i;

	//i = sh->m_pipe;
	//i = 0;

	path = cmd_path(cm);
	printf("AFUERA hijo PID %d CMD %s x = %d n_pipe %d\n", getpid(), cm->name, x, sh->n_pipe);

	if (!check_cmd(sh->cmd_lst->name) && sh->n_pipe > 0 && (x % 2 == 0))
	{
		printf("1ER IF Hijo PID %d CMD Ext %s \n", getpid(), cm->name);
		close(sh->pipe[x].p[OUT]);
		dup2(sh->pipe[x].p[IN], STDOUT_FILENO);
		close(sh->pipe[x].p[IN]);
		//printf("Salgo PROC 1\n");
	}


	if (sh->n_pipe > 0 && (x % 2 == 1))
	{
		printf("2DO IF Hijo PID %d CMD Ext %s \n", getpid(), cm->name);
		printf("path de %s es: %s \n", cm->name, path);
		close(sh->pipe[x -1].p[IN]);
		dup2(sh->pipe[x -1].p[OUT], STDIN_FILENO);
		close(sh->pipe[x -1].p[OUT]);
	}
	execve(path, cm->argvec, NULL);
}
