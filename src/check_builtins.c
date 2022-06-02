#include "minishell.h"

int	ft_size(t_tokens *lsist)
{
	t_tokens *begin;
	int i;

	i = 0;
	begin = lsist;
	while (begin)
	{
		if (begin->type == OPER)
			break;
		i++;
		begin = begin->next;
	}
	return (i);
}

void	ft_argvec_init(t_tokens *cmd)
{
	t_tokens	*begin;
	int			i;

	begin = cmd;
	i = 0;
	cmd->argve = malloc(sizeof(t_tokens) * ft_size(cmd) + 1);
	cmd->argve[ft_size(cmd)] = NULL;
	while (begin)
	{
		if (begin->type == OPER)
			break ;
		cmd->argve[i] = begin->str;
		begin = begin->next;
		i++;
	}
	printf("argvec0: %s argvec1: %s\n", cmd->argve[0], cmd->argve[1]);	
}

void check_builtins(t_sh *sh)
{
	char *s;
	char **line_split;

	s = sh->token_top->str;
	ft_argvec_init(sh->token_top);	
	line_split = sh->token_top->argve;
	if (!ft_strncmp(s, "exit", 5))
		ft_exit(sh->line);
	else if (!ft_strncmp(s, "pwd", 4))
		ft_getpwd();
	else if (!ft_strncmp(s, "echo", 5))
		ft_echo(line_split);
	else if (!ft_strncmp(s, "cd", 3))
		ft_cd(line_split);
	else if (!ft_strncmp(s, "export", 7))
		ft_export(line_split);
	else if (!ft_strncmp(s, "env", 4))
		ft_env();
}
