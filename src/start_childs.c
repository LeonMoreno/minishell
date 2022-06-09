#include "minishell.h"

void	dup_stdout(t_sh *sh, int x)
{
	close(sh->pipe[x].p[OUT]);
	dup2(sh->pipe[x].p[IN], STDOUT_FILENO);
	close(sh->pipe[x].p[IN]);
}

void	dup_stdout_un(t_sh *sh, int x)
{
	close(sh->pipe[x + 1].p[OUT]);
	dup2(sh->pipe[x + 1].p[IN], STDOUT_FILENO);
	close(sh->pipe[x + 1].p[IN]);
}

void	dup_stdin(t_sh *sh, int x)
{
	close(sh->pipe[x].p[IN]);
	dup2(sh->pipe[x].p[OUT], STDIN_FILENO);
	close(sh->pipe[x].p[OUT]);
}

void	dup_stdin_un(t_sh *sh, int x)
{
	close(sh->pipe[x + 1].p[IN]);
	dup2(sh->pipe[x +1].p[OUT], STDIN_FILENO);
	close(sh->pipe[x +1].p[OUT]);
}

void	start_child_builtins(t_cmd *cm, t_sh *sh, int x)
{
	printf("EXE CMD builtins %s PID %d\n", cm->name, getpid());
	dup_stdout(sh, x);
	start_builtins(cm, sh);
	exit (0);
}

void	start_child_cmdext(t_cmd *cm, t_sh *sh, int i, int x)
{
	char *path;

	path = cmd_path(cm);
	printf("AFUERA hijo i = %d PID %d CMD %s n_pipe %d x = %d\n", i, getpid(), cm->name, sh->n_pipe, x);

	if (!check_cmd(sh->cmd_lst->name) && sh->n_pipe > 0 && (i == 0))
	{
		printf("1ER IF Hijo PID %d CMD Ext %s \n", getpid(), cm->name);
		dup_stdout(sh, x);
	}
	else 
	{
		if ((i + 1) == sh->n_forks)
		{
			printf("2DO IF Hijo PID %d CMD Ext %s \n", getpid(), cm->name);
			if (sh->n_forks > 3 && (sh->n_forks % 2 == 0))
			{
				printf("HAY 4 COMMANDOS i = %d\n", i);
				dup_stdin_un(sh, x);
			}
			else
				dup_stdin(sh, x);
		}
		else
		{
			printf("HAY 3 COMMANDOS i = %d\n", i);
			dup_stdin(sh, x);
			
			dup_stdout_un(sh, x);
			//close(sh->pipe[x + 1].p[OUT]);
			//dup2(sh->pipe[x + 1].p[IN], STDOUT_FILENO);
			//close(sh->pipe[x + 1].p[IN]);
		}
	}
	execve(path, cm->argvec, NULL);
}
