#include "minishell.h"

void	start_child_builtins(t_cmd *cm, t_sh *sh)
{
	int i;

	i = 0;
	printf("EXE CMD builtins %s PID %d\n", cm->name, getpid());
	close(sh->pipe[i].p[OUT]);
	dup2(sh->pipe[i].p[IN], STDOUT_FILENO);
	close(sh->pipe[i].p[IN]);
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
		close(sh->pipe[x].p[OUT]);
		dup2(sh->pipe[x].p[IN], STDOUT_FILENO);
		close(sh->pipe[x].p[IN]);
	}
	else 
	{
		if ((i + 1) == sh->n_forks)
		{
			printf("2DO IF Hijo PID %d CMD Ext %s \n", getpid(), cm->name);
			printf("path de %s es: %s \n", cm->name, path);
			if (sh->n_forks > 3 && (sh->n_forks % 2 == 0))
			{
				printf("HAY 4 COMMANDOS i = %d\n", i);
				close(sh->pipe[x + 1].p[IN]);
				dup2(sh->pipe[x +1].p[OUT], STDIN_FILENO);
				close(sh->pipe[x + 1].p[OUT]);
			}
			else
			{
				close(sh->pipe[x].p[IN]);
				dup2(sh->pipe[x].p[OUT], STDIN_FILENO);
				close(sh->pipe[x].p[OUT]);
			}
	
		}
		else
		{
			printf("HAY 3 COMMANDOS i = %d\n", i);
			close(sh->pipe[x].p[IN]);
			dup2(sh->pipe[x].p[OUT], STDIN_FILENO);
			close(sh->pipe[x].p[OUT]);
			
			close(sh->pipe[x + 1].p[OUT]);
			dup2(sh->pipe[x + 1].p[IN], STDOUT_FILENO);
			close(sh->pipe[x + 1].p[IN]);
		}
	}
	execve(path, cm->argvec, NULL);
}
