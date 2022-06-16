#include "minishell.h"

int	ft_size(t_tokens *lsist, int mode)
{
	t_tokens	*begin;
	int			i;

	i = 0;
	begin = lsist;
	while (begin)
	{
		if (begin->type == PIPE)
			break;
		if (begin->next && begin->next->type != PIPE && begin->type == OPER)
			begin->next->type = OPERD;
		if (mode)
			i++;
		else if (begin->type == CMD || begin->type == ARG)
			i++;
		begin = begin->next;
	}
	return (i);
}
