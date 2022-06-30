/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:49:40 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/30 10:42:38 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_fill_args(t_tokens *begin, t_cmd *cm, char **temp, int len_a)
{
	int		i;
	bool	is_cmd;

	is_cmd = false;
	i = 0;
	while (begin)
	{	
		if ((begin->type == PIPE) || (begin->type == PARE && is_cmd))
			break ;
		if ((begin->type == PARE || begin->type == ARG) && is_cmd == false)
		{
			is_cmd = true;
			cm->name = begin->str;
			if (begin->type != PARE)
				begin->type = CMD;
		}
		if (begin->type == ARG && check_wild(begin->str))
			temp = openthydir(temp, begin->str, len_a, &i);
		else if (begin->type == ARG || begin->type == CMD)
			temp[i++] = ft_strdup(begin->str);
		//if (cm->name && (cm->name[0] == '(' || cm->name[0] == ')'))
		//	break ;
		begin = begin->next;
		
	}
	cm->argvec = temp;
	return (begin);
}

void	ft_argvec_init(t_tokens *index, t_cmd *this_cmd)
{
	t_tokens	*begin;
	char		**temp;
	int			len;

	len = ft_size(index, 0);
	begin = index;
	temp = malloc(sizeof(char *) * (ft_size(index, 0) + 1));
	ft_argvec_zero(temp, len + 1);
	begin = ft_fill_args(begin, this_cmd, temp, ft_size(index, 0));
	if (begin && begin->type == PIPE && oper_meta(begin->str, 0) == 38)
		this_cmd->oper = AND;
	if (begin && begin->type == PIPE && oper_meta(begin->str, 0) == 124)
		this_cmd->oper = OR;
}

void	ft_init_cmd(t_cmd *cmd, t_tokens *index)
{
	int			len_arg;
	int			i;
	t_tokens	*begin;

	begin = index;
	i = 0;
	cmd->fd_in = 0;
	cmd->fdin_str = NULL;
	len_arg = ft_size(index, 1);
	cmd->token_tab = malloc(sizeof(t_tokens *) * (len_arg + 1));
	cmd->token_tab[len_arg] = NULL;
	cmd->token_tab[len_arg] = NULL;
	cmd->argvec = NULL;
	while (i < len_arg)
	{
		cmd->token_tab[i] = begin;
		begin = begin->next;
		i++;
	}
	ft_argvec_init(index, cmd);
}

void	ft_create_cmd(t_sh *sh, bool *is_cmd, t_tokens *index)
{
	t_cmd	*begin;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->next = NULL;
	cmd->name = NULL;
	cmd->oper = 0;
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
	sh->n_pipe = 0;
	begin = sh->token_lst;
	while (begin)
	{
//		if (is_cmd && begin->type && begin->type != PARE)
		if (is_cmd && (begin->type == ARG || begin->type == PARE || begin->type == OPER))
			ft_create_cmd(sh, &is_cmd, begin);
		else if (begin->type == PIPE)//|| begin->type == PARE)
		{
			sh->n_pipe++;
			is_cmd = true;
		}
		if (begin->next && (begin->type == PARE || begin->next->type == PARE))
			is_cmd = true;
		begin = begin->next;
	}
	ft_check_redir_input(sh);
}
