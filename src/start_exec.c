/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:25:38 by lmoreno           #+#    #+#             */
/*   Updated: 2022/07/04 16:03:53 by agrenon          ###   ########.fr       */
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
			exit(0);
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
t_cmd	*exec_intern(t_sh *sh, t_cmd *cm, int fd_in)
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
	sh->last_oper = 0;
	while (tmp && sh->last_oper == 0)
	{
		chr_redir_out(tmp, '>');
		if (i < sh->n_pipe)
			pipe(sh->pipe[i].p);
		close_pipes(sh, i, &pi);
		start_cmd(tmp, sh, i, fd_in);
		sh->last_oper = tmp->oper;
		tmp = tmp->next;
		i++;
		fd_in = 0;
	}
	end_fork(sh);
	return (tmp);
}

void	subexec(t_sh *sh, t_cmd *cm, int *pi)
{
	char 	*path;
	char 	*join;
	int		status;
	pid_t 	pid;

	pid = fork();
	if (pid == 0)
	{
		(void) cm;
		(void) sh;
		path = getenv("PWD");
		join = ft_strjoin(path, "/");
		path = ft_strjoin(join, "./minishell");
		free(join);
		close (pi[OUT]);
		dup2(pi[IN], STDOUT_FILENO);
		close (pi[IN]);
		execve(path, cm->argvec, environ);
		perror("exc: ");
		ft_exit_fail(sh, NULL);
	}
	close(pi[IN]);
	waitpid(pid, &status, 0);
	sh->last_re = WEXITSTATUS(status);
}

t_cmd	*sub_cat(int *pi, t_cmd *cm)
{
	pid_t 	pid;
	char	*arg[2] = {"cat", NULL};

	pid = fork();
	if (pid == 0)
	{
		close (pi[IN]);
		dup2(pi[OUT], STDIN_FILENO);
		close (pi[OUT]);
		execve("/bin/cat", arg, NULL);
		perror("exc: ");
	}
	wait(NULL);
	return (cm->next);
}

t_cmd	*skip_job(t_cmd *cm, int OP)
{
	t_cmd	*begin;

	begin = cm;
	while (begin)
	{
		if (OP == OR && begin->oper == AND)
			return (begin->next);
		else if (OP == AND && begin->oper == OR)
			return (begin->next);
		begin = begin->next;
	}
	return (begin);
}

t_cmd	*special_redir(t_cmd *cm, int fd_pipe)
{
	char	buf[10000];
	int		i;
	int 	file;

	i = 0;
	ft_bzero(buf, 9999);
	read(fd_pipe, buf, 10000);
	while (cm->token_tab[i])
	{
		if (cm->token_tab[i]->type == OPER)
			file = open(cm->token_tab[i + 1]->str, O_CREAT | O_RDWR, 0000777); 
		if (cm->token_tab[i + 1] == NULL)
			break;
		i++;
	}
	write(file, buf, ft_strlen(buf));
	return (cm->next);
}

void	start_exec(t_sh *sh)
{
	t_cmd		*cm;
	t_tokens	*t;
	int			pi[2];

	sh->last_re = 0;
	cm = sh->cmd_lst;
	while (cm)
	{
		sh->last_oper = cm->oper;
		t = cm->token_tab[0];
		if (cm && t->type != PARE)
			cm = exec_intern(sh, cm, 0);
		else if (cm)
		{
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
		}
		if (sh->last_oper == AND && sh->last_re != 0)
			cm = skip_job(cm, AND);
		if (sh->last_oper == OR && sh->last_re == 0)
			cm = skip_job(cm, OR);
	}
}
