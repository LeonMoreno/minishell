#include "minishell.h"

//Creates a Token and its string according to the double quoting Rule
void    ft_double_quoting(t_sh *sh, int *i)
{
    int clone;
   /* int len;
    t_tokens *token;

   	token = ft_create_token(sh);
    */clone =  ft_quote_real(sh, *i, 1);
    /*len = clone - *i;
    token->str = ft_substr(sh->line, *i + 1, len - 1);
    printf("TOKEN created: %p string: %s\n", token, token->str);
    sh->n_tokens++;
    sh->start = -1;
    */*i = clone;
}

//Creates a Token and its string  according to the single quoting Rule.
void	ft_single_quoting(t_sh *sh, int *i)
{
	int	clone;
/*	int	len;
	t_tokens *token;

	token = ft_create_token(sh);
	*/clone =  ft_quote_real(sh, *i, 0);
	/*len = clone - *i;
	token->str = ft_substr(sh->line, *i + 1, len - 1);
	printf("TOKEN created: %p string: %s\n", token, token->str);
	sh->n_tokens++;
    sh->start = -1;
*/	*i = clone;
}

//Search for next " or ' index. Returns 0 if none.  
int		ft_quote_real(t_sh *sh, int i, int a)
{
	i = i + 1;
	while (sh->line[i])
	{
		if (sh->line[i] == 39 && a == 0)
			return (i);
		if (sh->line[i] == 34 && a == 1)
			return (i);
		i++;
	}
	return (0);
}
