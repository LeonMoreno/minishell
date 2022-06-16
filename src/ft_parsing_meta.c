/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_meta.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:05:39 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/16 19:05:43 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// PIPE : | = 124
// < = 60 > = 62
// & = 38

//If the Metacharacter is a pair, returns Metacharacter ascii
int	ft_double_meta(t_sh *sh, int i)
{
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

int	ft_parsing_meta(t_sh *sh, int i)
{
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
	if (sh->line[i] == 42)
		return (42);
	if (sh->line[i] == 38 && sh->line[i + 1] == 38)
		return (38);
	return (0);
}
