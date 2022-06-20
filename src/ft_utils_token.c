/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:18:08 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/20 15:02:07 by agrenon          ###   ########.fr       */
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

int	ft_parse_err(t_tokens *list)
{
	t_tokens	*begin;

	begin = list;
	while (begin)
	{
	//	printf("Type num: %d\n", begin->type);
		if ((begin->type == PIPE || begin->type == OPER) && !begin->next)
		{
			write(2, "parse error: operator has no argument\n", 38); 
			return (0);
		}
		if (begin->type == OPER && (begin->next->type == OPER
			|| begin->next->type == PIPE))
		{
			write(2, "parse error: too many operators in a row\n", 41);
			return (0);
		}
		begin = begin->next;
	}
	return (1);
}
