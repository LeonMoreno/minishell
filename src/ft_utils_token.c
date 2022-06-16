/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:18:08 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/16 19:18:09 by agrenon          ###   ########.fr       */
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
