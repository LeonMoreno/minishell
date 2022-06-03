#include "minishell.h"

void	free_cmd_lst(t_sh *sh)
{
	t_cmd	*begin;
	t_cmd	*temp;

	begin = NULL;
	if (sh->cmd_top)
		begin = sh->cmd_top;
	while (begin)
	{
		temp = begin;
		begin = begin->next;
//		free(begin->token_tab);
	//	if (begin->str_cmd)
	//		free (begin->str_cmd);
	//	if (begin->argvec)
	//		free(begin->argvec);
		free(temp);
	}
}

void    free_lst(t_sh *sh)
{
	t_tokens *begin;
	t_tokens *temp;

	free(sh->line);	
	begin = sh->token_top;
	while(begin)
	{
		temp = begin;
		begin = begin->next;
	//	if (begin->argve)
	//		free(begin->argve);
	//	if (begin->str)
	//		free(begin->str);
		free (temp);
    }
	free_cmd_lst(sh);
}
