#include "minishell.h"

void start_builtins(t_sh *sh)
{
	char *s;
	char **line_split;

	s = sh->token_lst->str;
	line_split = sh->cmd_lst->argvec;
	
	if (!ft_strncmp(s, "exit", 5))
		ft_exit(sh->line);
	else if (line_split[0] && !ft_strncmp(line_split[0], "pwd", 4))
		ft_getpwd();
	else if (line_split[0] && !ft_strncmp(line_split[0], "echo", 5))
		ft_echo(line_split);
	else if (line_split[0] && !ft_strncmp(line_split[0], "cd", 3))
		ft_cd(line_split);
	else if (line_split[0] && !ft_strncmp(line_split[0], "export", 7))
		ft_export(line_split);
	else if (line_split[0] && !ft_strncmp(line_split[0], "env", 4))
		ft_env();
	else if (line_split[0] && !ft_strncmp(line_split[0], "unset", 5))
		ft_unset(line_split);
}
