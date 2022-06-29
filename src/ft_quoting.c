/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quoting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:54:11 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/29 15:27:09 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Increments token string according to the double quoting Rule
char	*ft_double_quoting(t_sh *sh, int *i, char *temp)
{
	int		clone;
	char	*new_temp;

	*i = *i + 1;
	clone = ft_quote_real(sh, *i, 1);
	new_temp = temp;
	if (sh->line[*i] == 34)
		return (temp);
	while (*i < clone)
	{
		if (sh->line[*i] == '$')
			new_temp = ft_expansion(sh, i, new_temp);
		else if (sh->line[*i] != 34)
			new_temp = ft_prep_string(sh, &new_temp, i);
		*i = *i + 1;
	}	
	return (new_temp);
}

//Increment token string according to the single quoting Rule.
char	*ft_single_quoting(t_sh *sh, int *i, char *temp)
{
	int		clone;
	char	*new_temp;

	*i = *i + 1;
	clone = ft_quote_real(sh, *i, 0);
	new_temp = temp;
	if (sh->line[*i] == 39)
		return (temp);
	while (*i < clone)
	{
		if (sh->line[*i] != 39)
			new_temp = ft_prep_string(sh, &new_temp, i);
		*i = *i + 1;
	}
	return (new_temp);
}

//Search for next " or ' index. Returns 0 if none.  
int	ft_quote_real(t_sh *sh, int i, int a)
{
	i = i + 1;
	while (sh->line[i])
	{
		if (sh->line[i] == 39 && a == 0)
			return (i);
		if (sh->line[i] == 34 && a == 1)
			return (i);
		i++;
	}
	return (0);
}
