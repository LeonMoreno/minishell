/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_meta.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:28:36 by agrenon           #+#    #+#             */
/*   Updated: 2022/07/05 09:50:42 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// PIPE : | = 124
// < = 60 > = 62
// & = 38

//If the Metacharacter is a pair, returns Metacharacter ascii
int	ft_double_meta(t_sh *sh, int i)
{
	if (!sh->line)
		return (0);
	if (sh->line[i] == 60 && sh->line[i + 1] == 60)
		return (60);
	if (sh->line[i] == 62 && sh->line[i + 1] == 62)
		return (62);
	if (sh->line[i] == 124 && sh->line[i + 1] == 124)
		return (124);
	if (sh->line[i] == 38 && sh->line[i + 1] == 38)
		return (38);
	return (0);
}

int	oper_meta(char *str, int i)
{
	if (!str)
		return (0);
	if (str[i] == 124 && str[i + 1] == 124)
		return (124);
	if (str[i] == 38 && str[i + 1] == 38)
		return (38);
	return (0);
}

int	ft_parsing_meta(t_sh *sh, int i)
{
	if (i < 0)
		i = 0;
	if (sh->line[i] == 60 && sh->line[i + 1] == 60)
		return (60);
	if (sh->line[i] == 62 && sh->line[i + 1] == 62)
		return (62);
	if (sh->line[i] == 62)
		return (62);
	if (sh->line[i] == 60)
		return (60);
	if (sh->line[i] == 124 && sh->line[i + 1] == 124)
		return (124);
	if (sh->line[i] == 124)
		return (124);
	if (sh->line[i] == 38 && sh->line[i + 1] == 38)
		return (38);
	if (sh->line[i] == 40)
		return (40);
	if (sh->line[i] == 41)
		return (41);
	return (0);
}
