#include "minishell.h"


void ft_create_token(t_sh *sh, int start, int i)
{
	(void) sh;
	(void) start;
	(void) i;
	return ;
}

void line_parser(t_sh *sh)
{
    int i;
	int start;
    bool    s_quote;
    //bool    d_quote;

    i = 0;
	start = 0;
    while (i < ft_strlen(sh->line))
    {
        if (sh->line[i] != 39 && !s_quote)
            s_quote = true;
		else if (sh->line[i] != 39 && s_quote)
		{
			ft_create_token(sh, start, i);
			s_quote = false;
		}
		else if (start <= 0 && sh->line[i] > 32 && sh->line[i] < 127)
			start = i;
		else if (start <= 0 && sh->line[i] < 33)
			ft_create_token(sh, start, i);
		else
			continue ;
		i++;
	}
	//sh->line_split = ft_split(sh->line, ' ');
}
