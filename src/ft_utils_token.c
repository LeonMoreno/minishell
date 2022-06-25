/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:18:08 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/24 19:40:48 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size(t_tokens *lsist, int mode)
{
	t_tokens	*begin;
	int			i;

	i = 0;
	begin = lsist;
	while (begin)
	{
		if (begin->type == PIPE)
			break ;
		if (begin->next && begin->next->type != PIPE && begin->type == OPER)
			begin->next->type = OPERD;
		if (mode)
			i++;
		else if (begin->type == CMD || begin->type == ARG)
			i++;
		begin = begin->next;
	}
	return (i);
}

int	ft_message_err(t_tokens *begin, int n)
{
	int		a;
	char	*str;

	str = begin->str;
	a = 0;
	if (n == 0 && (begin->type == PIPE))
		a = write(2, "syntax error: line starts with operator -> ", 43);
	else if (n == 0 && begin->str[0] == '|' && begin->str[1] == '|')
		a = write(2, "syntax error: line starts with operator -> ", 43);
	else if (n == 0 && begin->str[0] == '&' && begin->str[1] == '&')
		a = write(2, "syntax error: line starts with operator -> ", 43);
	else if ((begin->type == PIPE || begin->type == OPER) && !begin->next)
		a = write(2, "parse error: operator has no argument -> ", 41);
	else if (begin->type == OPER && (begin->next->type == OPER
			|| begin->next->type == PIPE))
		a = write(2, "parse error: too many operators in a row -> ", 44);
	if (a)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	return (a);
}

int	ft_parse_err(t_tokens *list)
{
	t_tokens	*begin;
	int			i;

	i = 0;
	begin = list;
	while (begin)
	{
		if (ft_message_err(begin, i))
			return (0);
		i++;
		begin = begin->next;
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
