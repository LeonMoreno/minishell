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

void	ft_argvec_init(t_tokens *index, t_cmd *this_cmd)
{
	t_tokens	*begin;
	char		**temp;
	int			i;
	bool		is_cmd;

	is_cmd = false;
	begin = index;
	i = 0;
	temp = malloc(sizeof(char *) * ft_size(index) + 1);
	temp[ft_size(index)] = NULL;
	while (begin)
	{
		if (begin->type == PIPE)
			break ;
		else if (begin->next && begin->next->type != PIPE && begin->type == OPER)
			begin->next->type = OPERD;
		else if (begin->type == ARG && !is_cmd)
		{
			is_cmd = true;
			this_cmd->name = begin->str;
			begin->type = CMD;
		}
		if (begin->type == ARG	|| begin->type == CMD)
			temp[i++] = begin->str;
		if (begin->type == OPER)
			this_cmd->n_redir++;
		
		begin = begin->next;
	}
	this_cmd->argvec = temp;	
}


void	ft_init_cmd(t_cmd *cmd, t_tokens *index) 
{
	int			len_arg;
	int			i;
	t_tokens	*begin;

	begin = index;
	i = 0;
	len_arg = ft_size(index);
	cmd->token_tab = malloc(sizeof(t_tokens *) * len_arg + 1);
	cmd->token_tab[len_arg] = NULL;
	cmd->argvec = NULL;
	while (i < len_arg)
	{
		cmd->token_tab[i] = begin;
		//printf("      -TOKEN tab[ %d ]: %s   : Type %d\n",i, begin->str, begin-type);
		begin = begin->next;
		i++;
	}
	ft_argvec_init(index, cmd);
	i = 0;
	while (cmd->argvec[i])
	{
		//printf("   -Argvec[ %d ]: %s\n", i, cmd->argvec[i]);
		i++;
	}
	
}

void	ft_create_cmd(t_sh *sh, bool *is_cmd, t_tokens *index)
{
	t_cmd	*begin;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->next = NULL;
	cmd->n_redir = 0;
	*is_cmd = false;
	if (!sh->cmd_lst)
	{
		sh->cmd_lst = cmd;
		ft_init_cmd(cmd, index);
		return ;
	}
	begin = sh->cmd_lst;
    while (begin)
    {
		if (!begin->next)
			break ;
		begin = begin->next;
	}
	begin->next = cmd;
	ft_init_cmd(cmd, index);
}


void	ft_init_cmd_lst(t_sh *sh)
{
	t_tokens	*begin;
	bool		is_cmd;

	is_cmd = true;
	sh->n_pipe = 0; //In each line pipe begin in cero #LEO
	begin = sh->token_lst;
	while (begin)
	{
		if (begin->type != PIPE && is_cmd)
			ft_create_cmd(sh, &is_cmd, begin);
		else if (begin->type == PIPE)
		{
			sh->n_pipe++; // add number pipes #LEO
			is_cmd = true;
		}
		begin = begin->next;
	}
}

