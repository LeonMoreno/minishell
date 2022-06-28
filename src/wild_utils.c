/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:38:39 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/27 18:44:43 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_accepted(char *wild_str, char *str)
{
	if (wild_str[0] != '.' && (!ft_strncmp(str, ".", 2)
			|| !ft_strncmp(str, "..", 3)))
		return (0);
	if (wild_str[0] != '.' && str[0] == '.')
		return (0);
	if (ft_wild_split_ncmp(wild_str, str))
		return (1);
	return (0);
}

t_argve	*argve_lst(t_argve *lst, char *str)
{
	t_argve	*new_arg;
	t_argve	*begin;

	new_arg = malloc(sizeof(t_argve));
	new_arg->next = NULL;
	new_arg->str = ft_strdup(str);
	if (!lst)
		lst = new_arg;
	else
	{
		begin = lst;
		while (begin)
		{
			if (!begin->next)
				break ;
			begin = begin->next;
		}
		begin->next = new_arg;
	}
	return (lst);
}

int	keep_traditions(char **argvec, int old, int i, char **new_argvec)
{
	i = 0;
	while (i < old)
	{
		new_argvec[i] = ft_strdup(argvec[i]);
		free(argvec[i]);
		i++;
	}
	free(argvec);
	return (i);
}

char	**new_argve_tab(char **argvec, t_argve *lst, int old, char **tab)
{
	int		len;
	char	**new_argvec;
	int		i;
	t_argve	*begin;

	len = ft_size_arr(argvec) + size_alst(lst) - 1;
	i = len + old - 1;
	if (!lst)
		i++;
	new_argvec = malloc(sizeof(char *) * (i + 1));
	ft_argvec_zero(new_argvec, i + 1);
	begin = lst;
	i = keep_traditions(argvec, ft_size_arr(argvec), i, new_argvec);
	while (i < len + 1 && lst)
	{
		new_argvec[i++] = ft_strjoin(tab[0], begin->str);
		begin = begin->next;
	}
	if (!lst)
		new_argvec[i++] = ft_strjoin(tab[0], tab[1]);
	return (new_argvec);
}
