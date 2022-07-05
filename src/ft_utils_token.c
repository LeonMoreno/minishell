/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:18:08 by agrenon           #+#    #+#             */
/*   Updated: 2022/07/05 12:32:20 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_argvec_zero(char **argvec, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		argvec[i] = NULL;
		i++;
	}
	return ;
}

int	ft_size(t_tokens *lsist, int mode)
{
	t_tokens	*begin;
	int			i;

	i = 0;
	begin = lsist;
	if (begin->type == PARE)
		return (1);
	while (begin)
	{
		if (begin->type == PIPE || begin->type == PARE)
			break ;
		if (begin->next && begin->next->type != PIPE && begin->type == OPER
			&& begin->next->type != PARE)
			begin->next->type = OPERD;
		if (mode)
			i++;
		else if (begin->type == CMD || begin->type == ARG)
			i++;
		begin = begin->next;
	}
	return (i);
}

int	ft_message_err(t_tokens *b, int n)
{
	int		a;

	a = 0;
	if (n == 0 && (b->type == PIPE))
		a = write(2, "syntax error: line starts with operator -> ", 43);
	else if (n == 0 && b->str[0] == '|' && b->str[1] == '|')
		a = write(2, "syntax error: line starts with operator -> ", 43);
	else if (n == 0 && b->str[0] == '&' && b->str[1] == '&')
		a = write(2, "syntax error: line starts with operator -> ", 43);
	else if ((b->type == PIPE || b->type == OPER) && !b->next)
		a = write(2, "parse error: operator has no argument -> ", 41);
	else if (b->type == OPER && (b->next->type == OPER
			|| b->next->type == PIPE))
		a = write(2, "parse error: too many operators in a row -> ", 44);
	else if (b->type == OPER && (b->str[0] == '>' || b->str[0] == '<')
		&& (!b->next || b->next->type == PIPE || b->next->type == PARE))
		a = write(2, "parse error: redirection has no operand -> ", 43);
	if (a)
	{
		write(2, b->str, ft_strlen(b->str));
		write(2, "\n", 1);
	}
	return (a);
}

int	ft_parse_err(t_tokens *list)
{
	t_tokens	*begin;
	int			i;
	int			left;
	int			right;

	i = 0;
	left = 0;
	right = 0;
	begin = list;
	while (begin)
	{
		if (ft_message_err(begin, i) || ft_messa_pare(begin, &left, &right))
			return (0);
		i++;
		begin = begin->next;
	}
	if (left != right)
	{
		write(2, "syntax error: parenthesis can't be closed -> )", 45);
		return (0);
	}
	return (1);
}

void	ft_exit_here(char *temp, t_sh *sh)
{
	if (temp)
		free(temp);
	free_doble_arr(environ);
	free_lst(sh);
	close(4);
	exit(0);
}
