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
			this_cmd->str_cmd = begin->str;
			begin->type = CMD;
		}
		if (begin->type == ARG	|| begin->type == CMD)
			temp[i++] = begin->str;
		//printf("String : %s TYPE : %d\n", temp[i], begin->type);
		begin = begin->next;
		//i++;
	}
	this_cmd->argvec = temp;	
	//printf("argvec0: %s argvec1: %s\n", temp[0], temp[1]);
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
	while (i < len_arg)
	{
		cmd->token_tab[i] = begin;
	//	printf("      -TOKEN tab[ %d ]: %s\n",i, begin->str);
		begin = begin->next;
		i++;
	}
	ft_argvec_init(index, cmd);
	i = 0;
	printf("COMMANDE: %s argve_Len: %d\n", cmd->str_cmd, len_arg);
	while (cmd->argvec[i])
	{
		printf("   -Argvec[ %d ]: %s\n", i, cmd->argvec[i]);
		i++;
	}
	
}

void	ft_create_cmd(t_sh *sh, bool *is_cmd, t_tokens *index)
{
	t_cmd	*begin;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->next = NULL;
	*is_cmd = false;
	if (!sh->cmd_top)
	{
		sh->cmd_top = cmd;
		ft_init_cmd(cmd, index);
		printf("INIT_CMD: %s\n", cmd->str_cmd);
		return ;
	}
	begin = sh->cmd_top;
    while (begin)
    {
		if (!begin->next)
			break ;
		begin = begin->next;
	}
	printf("INIT_CMD: %s\n", cmd->str_cmd);
	begin->next = cmd;
	ft_init_cmd(cmd, index);
	//return (cmd);
}


void	ft_init_cmd_lst(t_sh *sh)
{
	t_tokens	*begin;
	bool		is_cmd;


	is_cmd = true;
	begin = sh->token_top;
	while (begin)
	{
		if (begin->type != PIPE && is_cmd)
			ft_create_cmd(sh, &is_cmd, begin);
		else if (begin->type == PIPE)
			is_cmd = true;
		begin = begin->next;
	}
	printf("INIT_CMD_LST: %s\n", sh->cmd_top->token_tab[0]->str);
}

