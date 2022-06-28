/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2buil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:19:45 by lmoreno           #+#    #+#             */
/*   Updated: 2022/06/28 15:22:15 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_arr(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i] && tab[i][0])
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

/**
 * @brief: malloc pour les pipes
 * @sh->pip : ptr struct s_pip
 */
void	start_pipex(t_sh *sh)
{
	if (sh->n_pipe)
		sh->pipe = malloc(sizeof(t_pip) * sh->n_pipe);
}

/**
 * @brief: start and malloc var sh->id_f aka var_forks
 * @i : incrementa solo si hay pipex
 * Return : number forks malloces
 */
int	init_fork(t_sh *sh)
{
	int		i;
	t_cmd	*cm;

	cm = sh->cmd_lst;
	i = 0;
	while (cm)
	{
		if (!check_cmd(sh->cmd_lst->name) || sh->n_pipe > 0)
			i++;
		cm = cm->next;
	}
	if (i > 0)
		sh->id_f = malloc(sizeof(pid_t) * i);
	return (i);
}
