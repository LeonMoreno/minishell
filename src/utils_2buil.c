/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2buil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:19:45 by lmoreno           #+#    #+#             */
/*   Updated: 2022/07/08 11:07:22 by agrenon          ###   ########.fr       */
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
int	init_fork(t_sh *sh, t_cmd *top)
{
	int		i;
	t_cmd	*cm;

	cm = top;
	i = 0;
	while (cm && cm->name)
	{
		if ((!check_cmd(cm->name) || sh->n_pipe > 0))
				i++;
		if (cm->oper)
			break ;
		cm = cm->next;
	}
	if (i > 0)
		sh->id_f = malloc(sizeof(pid_t) * i);
	return (i);
}

void	ft_perror(char *s, t_sh *sh)
{
	sh->last_re = 1;
	perror(s);
}
