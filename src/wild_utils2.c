/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:29:13 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/27 18:52:57 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wild_next(char *wild_str, int j)
{
	int	i;

	i = j;
	while (wild_str[i + 1] == '*')
	{
		if (wild_str[i + 1] == '\0')
			break ;
		i++;
	}
	return (i);
}

int	wild_str_good(char *wstr, char *str, int index)
{
	int	i;

	if (!wstr)
		return (1);
	i = 0;
	while (wstr[i])
	{
		if (wstr[i] != str[index])
			return (0);
		else if (!str[index])
			return (0);
		index++;
		i++;
	}
	return (i);
}

int	ft_check_last(char **split, char *str)
{
	int	last_len;
	int	len;
	int	a;

	a = ft_size_arr(split) - 1;
	len = ft_strlen(str);
	last_len = ft_strlen(split[a]);
	return (wild_str_good(split[a], str, len - last_len));
}

int	ft_wild_good(char **split, bool first, bool last, char *str)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (!first && !wild_str_good(split[0], str, 0))
		return (0);
	if (!last && !ft_check_last(split, str))
		return (0);
	while (str[i])
	{
		if (split[a] && str[i] == split[a][0]
				&& wild_str_good(split[a], str, i))
		{
			i = i + wild_str_good(split[a], str, i) - 1;
			a++;
		}
		i++;
	}
	if (a != ft_size_arr(split))
		return (0);
	return (1);
}

int	ft_wild_split_ncmp(char *wild, char *str)
{
	bool	first;
	bool	last;
	char	**wsplit;

	wsplit = ft_split(wild, '*');
	first = false;
	last = false;
	if (wild[0] == '*')
		first = true;
	if (wild[ft_strlen(wild) - 1] == '*')
		last = true;
	if (!wsplit[0])
	{
		free_doble_arr(wsplit);
		return (1);
	}
	if (ft_wild_good(wsplit, first, last, str))
	{
		free_doble_arr(wsplit);
		return (1);
	}
	free_doble_arr(wsplit);
	return (0);
}
