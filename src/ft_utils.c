#include "minishell.h"


//Prints info on all commands
void    ft_print_cmds(t_sh *sh)
{
	t_cmd	*begin;
    int		i;
    int		j;

	i = 1;
	begin  = sh->cmd_lst;
	while (begin)
	{
		j = 0;
		while (begin->argvec[j])
			j++;
		printf("CMD %d: [ %s ]  has %d args and %d redirections\n", i, begin->name, j - 1, begin->n_redir);
		i++;
		begin = begin->next;
	}
}

void	free_cmd_lst(t_sh *sh)
{
	t_cmd	*begin;
	t_cmd	*temp;

	begin = NULL;
	if (sh->cmd_lst)
		begin = sh->cmd_lst;
	while (begin)
	{
		temp = begin;
		begin = begin->next;
		//if (begin->token_tab)
		//	free(begin->token_tab);
		//if (begin->name)
		//	free (begin->name);
		//if (begin->argvec)
		//	free(begin->argvec);
		free(temp);
	}
}

void    free_lst(t_sh *sh)
{
	t_tokens *begin;
	t_tokens *temp;

	free(sh->line);
	begin = sh->token_lst;
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

/**
 * end_fork - if we are fork - wait childs exit
 * @status: save status child
 * @n_f: number of forks
 *
 */
void	end_fork(t_sh *sh)
{
	int	i;
	int	status;

	i = 0;
	while (i < sh->n_forks)
	{
		waitpid(sh->id_f[i], &status, 0);
		if (sh->pipe[i].p[IN])
		{
			close(sh->pipe[i].p[OUT]);
			close(sh->pipe[i].p[IN]);
			printf("Cerrado *PIPE* %d\n", i);
		}
		printf("Cerrado fork %d\n", i);
		i++;
	}
}
