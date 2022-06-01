#include "minishell.h"

void check_builtins(char *line)
{
	char **line_split;

	line_split = ft_split(line, ' ');
	if (!ft_strncmp(line_split[0], "exit", 5))
		ft_exit(line);
	else if (!ft_strncmp(line_split[0], "pwd", 4))
		ft_getpwd();
	else if (!ft_strncmp(line_split[0], "echo", 5))
		ft_echo(line_split);
	else if (!ft_strncmp(line_split[0], "cd", 3))
		ft_cd(line_split);
}
