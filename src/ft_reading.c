#include "minishell.h"

void	ft_quote(t_sh *sh, bool *s_quote, bool *d_quote, int i)
{
	if (s_quote && sh->line[i] == 39)
		*s_quote = false;
	else if (d_quote && sh->line[i] == 34)
		*d_quote = false;
	else if (!d_quote && sh->line[i] == 34)
		*d_quote = true;
	else if (!s_quote && sh->line[i] == 39)
		*s_quote = true;
}

void	ft_count_quote(t_sh *sh)
{
	int		i;
	int		count;
	char	*temp;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	(void) count;
	while (sh->line[i])
	{
		ft_quote(sh, &s_quote, &d_quote, i);
		if (sh->line[i] == '\n')
		{
			temp = NULL;
		}
		i++;
	}
	return ; 
}
