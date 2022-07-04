/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:25:38 by lmoreno           #+#    #+#             */
/*   Updated: 2022/07/04 16:06:14 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief: begin start commands extern & builtins
 * if there pipe || are builtins exec builtins with in fork
 * if no pipe builtins exec without fork
 * if cmd has a fd_in , Dup2 stdin
 */
void	start_cmd(t_cmd *cm, t_sh *sh, int i, int fd_in)
{
	if (!check_cmd(cm->name) || sh->n_pipe > 0)
	{
		sh->id_f[i] = fork();
		if (sh->id_f[i] == 0)
		{
			if (fd_in)
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
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

t_cmd	*start_exec_next(t_tokens *t, t_sh *sh, t_cmd *cm)
{
	int	pi[2];

	if (t->str[0] == '(' && sh->last_re == 0)
	{
		pipe(pi);
		subexec(sh, cm, pi);
		cm = cm->next;
	}
	else if (t->str[0] == ')' && (cm->oper != 0 || !cm->next))
		cm = sub_cat(pi, cm);
	else if (t->str[0] == ')' && (cm->oper == 0 && !cm->next->name))
		cm = special_redir(cm->next, pi[OUT]);
	else if (t->str[0] == ')' && (cm->oper == 0 && cm->next))
		cm = exec_intern(sh, cm->next, pi[OUT]);
	return (cm);
}

void	start_exec(t_sh *sh)
{
	t_cmd		*cm;
	t_tokens	*t;

	sh->last_re = 0;
	cm = sh->cmd_lst;
	while (cm)
	{
		sh->last_oper = cm->oper;
		t = cm->token_tab[0];
		if (cm && t->type != PARE)
			cm = exec_intern(sh, cm, 0);
		else if (cm)
			cm = start_exec_next (t, sh, cm);
		if (sh->last_oper == AND && sh->last_re != 0)
			cm = skip_job(cm, AND);
		if (sh->last_oper == OR && sh->last_re == 0)
			cm = skip_job(cm, OR);
	}
}
