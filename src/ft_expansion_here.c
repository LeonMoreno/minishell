/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_here.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:42:16 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/28 14:42:31 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_end_expansion(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34 || line[i] < 33)
			break ;
		if (line[i + 1] == '$' || line[i] == '?')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

static char	*ft_compare_env(t_sh *sh, char *line, int start, int end)
{
	char	*expan;
	char	*found;

	expan = ft_substr(line, start + 1, end - start - 1);
	if (expan[0] == '?')
		found = ft_strdup(ft_itoa(sh->last_re));
	else
	{
		found = getenv(expan);
		if (found)
			found = ft_strdup(found);
		free(expan);
	}
	return (found);
}

char	*ft_expansion_here(t_sh *sh, char *line, int *i, char *temp)
{
	int		end;
	char	*new_temp;
	char	*found;

	end = ft_end_expansion(line, *i);
	found = ft_compare_env(sh, line, *i, end);
	*i = end - 1;
	if (temp && found)
		new_temp = ft_strjoin(temp, found);
	else if (!found)
		return (temp);
	else
		return (found);
	free(temp);
	free(found);
	return (new_temp);
}

static char	*ft_prep_here(char **temp, char *line, int i)
{
	char	this_char[2];
	char	*new_temp;

	this_char[0] = line[i];
	this_char[1] = '\0';
	if (!*temp)
		new_temp = ft_strdup(this_char);
	else
		new_temp = ft_strjoin(*temp, this_char);
	if (*temp)
	{
		free(*temp);
		*temp = NULL;
	}
	return (new_temp);
}

char	*ft_expand_here(t_sh *sh, char *line)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] > 32 && line[i + 1] != 34
			&& line[i + 1] != 39)
			temp = ft_expansion_here(sh, line, &i, temp);
		else
			temp = ft_prep_here(&temp, line, i);
		i++;
	}
	free(line);
	return (temp);
}
