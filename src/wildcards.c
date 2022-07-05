/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:37:30 by agrenon           #+#    #+#             */
/*   Updated: 2022/07/05 17:04:21 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	**join_path(char **split, char **tab)
{
	int		i;
	char	*temp;
	char	*path;

	path = NULL;
	i = 0;
	while (i < ft_size_arr(split) - 2)
	{
		if (i == 0)
			temp = ft_strjoin(split[i], "/");
		else
			temp = ft_strjoin(path, "/");
		if (path)
			free(path);
		path = ft_strjoin(temp, split[i + 1]);
		free(temp);
		i++;
	}
	temp = ft_strjoin(path, "/");
	free(path);
	tab[0] = temp;
	tab[1] = ft_strdup(split[ft_size_arr(split) - 1]);
	free_doble_arr(split);
	return (tab);
}

char	**str_folder(char *str)
{
	char	**temp;
	char	**tab;
	char	*only_two;

	tab = malloc(sizeof(char *) * 3);
	tab[2] = NULL;
	temp = ft_split(str, '/');
	if (!temp[1])
	{
		tab[0] = ft_strdup(".");
		tab[1] = ft_strdup(temp[0]);
		free_doble_arr(temp);
		return (tab);
	}
	else if (temp[2])
		return (join_path(temp, tab));
	free(tab);
	only_two = ft_strjoin(temp[0], "/");
	free(temp[0]);
	temp[0] = only_two;
	return (temp);
}

char	**ft_add_argvec(char **argvec, char **tab, DIR *d, int len)
{
	struct dirent	*dir;
	t_argve			*wild_lst;
	char			**new_argvec;

	wild_lst = NULL;
	dir = readdir(d);
	while (dir)
	{
		if (ft_is_accepted(tab[1], dir->d_name))
			wild_lst = argve_lst(wild_lst, dir->d_name);
		dir = readdir(d);
	}
	if (!ft_strncmp(tab[0], ".", 2))
	{
		free(tab[0]);
		tab[0] = ft_strdup("\0");
	}
	new_argvec = new_argve_tab(argvec, wild_lst, len, tab);
	ft_free_argve_lst(wild_lst);
	return (new_argvec);
}

char	**openthydir(char **argvec, char *wild_str, int len_argve, int *i)
{
	DIR		*d;
	char	**split;
	char	**new_argvec;
	int		j;

	split = NULL;
	split = str_folder(wild_str);
	d = opendir(split[0]);
	if (!d)
	{
		argvec[*i] = wild_str;
		*i = *i + 1;
		free_doble_arr(split);
		return (argvec);
	}
	new_argvec = ft_add_argvec(argvec, split, d, len_argve);
	j = 0;
	while (new_argvec[j])
		j++;
	*i = j;
	free_doble_arr(split);
	closedir(d);
	return (new_argvec);
}
