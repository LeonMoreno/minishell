/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:25:38 by lmoreno           #+#    #+#             */
/*   Updated: 2022/07/05 12:38:22 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief: begin start commands extern & builtins
 * if there pipe || are builtins exec builtins with in fork
 * if no pipe builtins exec without fork
 * if cmd has a fd_in , Dup2 stdin
 */
void	start_cmd(t_cmd *cm, t_sh *sh, int i)
{
	if (!check_cmd(cm->name) || sh->n_pipe > 0)
	{
		sh->id_f[i] = fork();
		if (sh->id_f[i] == 0)
		{
			if (cm->fdin_str)
			{
				close(cm->fd_in);
				cm->fd_in = open(cm->fdin_str, O_RDONLY, 777);
			}
			if (cm->fd_in > 2)
				dup2(cm->fd_in, 0);
			if (check_cmd(cm->name) && cm->fd_in != -1)
				start_child_builtins(cm, sh, i);
			else if (cm->fd_in != -1)
				start_child_cmdext(cm, sh, i);
		}
	}
	else
		start_builtins(cm, sh);
}

void	close_pipes(t_sh *sh, int i, int *pi)
{
	if (i != 0 && i % 2 == 0)
	{
		close(sh->pipe[*pi].p[OUT]);
		close(sh->pipe[*pi].p[IN]);
		*pi = *pi + 1;
	}
	if (i != 1 && i % 2 == 1)
	{
		close(sh->pipe[*pi].p[OUT]);
		close(sh->pipe[*pi].p[IN]);
		*pi = *pi + 1;
	}
}

int	chr_pipe(t_cmd *cm)
{
	int		i;
	t_cmd	*t;

	t = cm;
	i = 0;
	while (t)
	{
		if (t->name && !t->oper && t->next)
			i++;
		if (t->oper)
			break ;
		t = t->next;
	}
	return (i);
}

/**
 * @brief: start fork/pipes/commands/EndForks
 * @i: use for index var sh->id_f: fork
 * @n_f: number of forks
 * @x: index number pipex, increment chaque 2 commands
 */
t_cmd	*exec_intern(t_sh *sh, t_cmd *cm)
{
	int		i;
	int		pi;
	t_cmd	*tmp;

	tmp = cm;
	i = 0;
	pi = 0;
	sh->n_pipe = chr_pipe(cm);
	start_pipex(sh);
	sh->n_forks = init_fork(sh, cm);
	while (tmp && sh->last_oper == 0)
	{
		chr_redir_out(tmp, '>');
		if (i < sh->n_pipe)
			pipe(sh->pipe[i].p);
		close_pipes(sh, i, &pi);
		start_cmd(tmp, sh, i);
		sh->last_oper = tmp->oper;
		tmp = tmp->next;
		i++;
	}
	end_fork(sh);
	return (tmp);
}

void	start_exec(t_sh *sh)
{
	t_cmd	*cm;

	cm = sh->cmd_lst;
	while (cm)
	{
		cm = exec_intern(sh, cm);
		if (sh->last_oper == 5 && sh->last_re != 0)
			cm = cm->next;
		if (sh->last_oper == 6 && sh->last_re == 0)
			break ;
		sh->last_oper = 0;
	}
}
