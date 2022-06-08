#include "minishell.h"

void	start_child_builtins(t_cmd *cm, t_sh *sh)
{
	printf("EXE CMD builtins %s PID %d\n", cm->name, getpid());
	close(sh->pipe->p[OUT]);

	dup2(sh->pipe[0].p[IN], STDOUT_FILENO);
	close(sh->pipe[0].p[IN]);
	start_builtins(cm, sh);
	exit (0);
}

void	start_child_cmdext(t_cmd *cm, t_sh *sh)
{
	//char c;
	printf("Hijo PID %d CMD Ext %s \n", getpid(), cm->name);

	//c = 'A';
	s_parsing_cmd(cm, sh);
	if (sh->n_pipe > 0)
	{
		close(sh->pipe[0].p[IN]);
		dup2(sh->pipe[0].p[OUT], STDIN_FILENO);
	}
	
	close(sh->pipe->p[OUT]);
	//read(0, &c, 1);
//	printf("%c\n", c);
	exit (0);
}
