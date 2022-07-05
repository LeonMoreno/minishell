/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:25:33 by lmoreno           #+#    #+#             */
/*   Updated: 2022/07/05 13:31:01 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_redir_fork(t_cmd *cm, t_sh *sh)
{
	(void) sh;
	start_redir(cm);
}

void	chr_redir_out(t_cmd *cm, char c)
{
	t_tokens	**t;
	int			n;
	int			i;

	i = 0;
	n = 0;
	t = cm->token_tab;
	while (t[i])
	{
		if (t[i]->type == OPER && ft_strchr(t[i]->str, c))
			n++;
		i++;
	}
	cm->n_r_out = n;
}

void	start_redir(t_cmd *cm)
{
	t_tokens	**t;
	int			i;
	int			j;

	t = cm->token_tab;
	i = 0;
	j = 0;
	cm->fd_out = malloc(sizeof(int) * cm->n_r_out);
	if (!cm->fd_out)
		exit (1);
	while (t[i])
	{
		if (!ft_strncmp(t[i]->str, ">", 2))
			cm->fd_out[j++] = open(t[i + 1]->str,
					O_CREAT | O_TRUNC | O_RDWR, 0000644);
		if (!ft_strncmp(t[i]->str, ">>", 3))
			cm->fd_out[j++] = open(t[i + 1]->str, O_CREAT
					| O_RDWR | O_APPEND, 0000644);
		i++;
	}
	dup2(cm->fd_out[j - 1], STDOUT_FILENO);
}

void	close_redir_buil(t_sh *sh, t_cmd *cm)
{
	int	j;

	j = 0;
	dup2(sh->true_fd_out, STDOUT_FILENO);
	while (j < cm->n_r_out)
		close(cm->fd_out[j++]);
	close(sh->true_fd_out);
	free(cm->fd_out);
}
