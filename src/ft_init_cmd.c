/* ************************************************************************** */
	//		free(begin->fds);
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:49:40 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/16 18:50:30 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_attribute_argvec(t_tokens *begin, bool *is_cmd, t_cmd *this_cmd)
{
	if (begin->type == ARG && *is_cmd == false)
	{
		*is_cmd = true;
		this_cmd->name = begin->str;
		begin->type = CMD;
	}
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
	temp = malloc(sizeof(char *) * (ft_size(index, 0) + 1));
	temp[ft_size(index, 0)] = NULL;
	while (begin)
	{	
		if (begin->type == PIPE)
			break ;
		ft_attribute_argvec(begin, &is_cmd, this_cmd);
		if (begin->type == ARG || begin->type == CMD)
			temp[i++] = begin->str;
//		if (begin->type == OPER)
//			this_cmd->n_redir++;
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
//	cmd->n_redir = 0;
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
		if (begin->type != PIPE && is_cmd)
			ft_create_cmd(sh, &is_cmd, begin);
		else if (begin->type == PIPE)
		{
			sh->n_pipe++;
			is_cmd = true;
		}
		begin = begin->next;
	}
	ft_check_redir_input(sh);
}
