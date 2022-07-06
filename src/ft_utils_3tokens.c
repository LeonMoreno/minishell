/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:32:46 by agrenon           #+#    #+#             */
/*   Updated: 2022/07/06 17:32:48 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_pare_check(t_sh *sh)
{
	int		left;
	int		right;
	int		i;
	bool	valid;

	valid = true;
	left = 0;
	right = 0;
	i = 0;
	while (sh->line[i])
	{
		if ((sh->line[i] == 34 || sh->line[i] == 39) && valid)
			valid = false;
		else if ((sh->line[i] == 34 || sh->line[i] == 39) && !valid)
			valid = true;
		if (sh->line[i] == '(' && valid)
			left++;
		if (sh->line[i] == ')' && valid)
			right++;
		i++;
	}
	if (right != left)
		return (1);
	return (0);
}
