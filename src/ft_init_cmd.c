#include "minishell.h"

int	ft_size(t_tokens *lsist)
{
	t_tokens *begin;
	int i;

	i = 0;
	begin = lsist;
	while (begin)
	{
		if (begin->type == PIPE)
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
		if (begin->type == PIPE)
			break ;
		cmd->argve[i] = begin->str;
		begin = begin->next;
		i++;
	}
	//printf("argvec0: %s argvec1: %s\n", cmd->argve[0], cmd->argve[1]);
}

