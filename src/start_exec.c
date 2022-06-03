#include "minishell.h"

int check_builtins(char *s)
{
	if(!ft_strncmp(s, "exit", 5))
			return (1);
	if(!ft_strncmp(s, "pwd", 4))
			return (1);
	if(!ft_strncmp(s, "cd", 3))
			return (1);
	if(!ft_strncmp(s, "export", 7))
			return (1);
	if(!ft_strncmp(s, "env", 4))
			return (1);
	if(!ft_strncmp(s, "unset", 5))
			return (1);
	if(!ft_strncmp(s, "echo", 5))
			return (1);
	return (0);
}


void start_exec(t_sh *sh)
{
	if (check_builtins(sh->cmd_lst->name))
		start_builtins(sh);
}
