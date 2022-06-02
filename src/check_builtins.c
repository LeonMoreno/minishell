#include "minishell.h"

void check_builtins(t_sh *sh)
{
	char **line_split;

	line_split = ft_split(sh->line, ' ');
	if (!ft_strncmp(line_split[0], "exit", 5))
		ft_exit(sh->line);
	else if (!ft_strncmp(line_split[0], "pwd", 4))
		ft_getpwd();
	else if (!ft_strncmp(line_split[0], "echo", 5))
		ft_echo(line_split);
	else if (!ft_strncmp(line_split[0], "cd", 3))
		ft_cd(line_split);
	else if (!ft_strncmp(line_split[0], "export", 7))
		ft_export(line_split);
	else if (!ft_strncmp(line_split[0], "env", 4))
		ft_env();
}
