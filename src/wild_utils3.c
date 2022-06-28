/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:33:14 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/27 18:21:52 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_alst(t_argve *lst)
{
	int		i;
	t_argve	*begin;

	begin = lst;
	if (!begin)
		return (0);
	i = 0;
	while (begin)
	{
		if (begin->str[0] == '\0')
			break ;
		begin = begin->next;
		i++;
	}
	return (i);
}

int	check_wild(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_argve_lst(t_argve *lst)
{
	t_argve	*begin;
	t_argve	*temp;

	begin = lst;
	while (begin)
	{
		temp = begin;
		begin = begin->next;
		free(temp->str);
		free(temp);
	}
	return ;
}
