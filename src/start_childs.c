#include "minishell.h"

void	start_child_builtins(t_cmd *cm, t_sh *sh)
{
	printf("EXE CMD builtins %s PID %d\n", cm->name, getpid());
	start_builtins(cm, sh);
	exit (0);
}

void	start_child_cmdext(t_cmd *cm, t_sh *sh)
{
	sh->start = 0;
	printf("Hijo PID %d CMD Ext %s \n", getpid(), cm->name);
	exit (0);
}
