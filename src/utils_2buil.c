/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2buil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:19:45 by lmoreno           #+#    #+#             */
/*   Updated: 2022/06/24 19:40:05 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_arr(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_chr_n(char *s, int *n, int *ctr)
{
	int	i;
	int	ch;

	ch = 0;
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
		{
			ch = 7;
			break ;
		}
		i++;
	}
	if (ch == 0)
	{
		*n = 2;
		*ctr = 1;
	}
}
