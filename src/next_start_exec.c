/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_start_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:12:05 by lmoreno           #+#    #+#             */
/*   Updated: 2022/07/07 14:11:35 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
	sh->n_forks = init_fork(sh, cm);
	while (tmp && sh->last_oper == 0)
	{
		printf("sh->n_forks = %d\n", sh->n_forks);
		chr_redir_out(tmp, '>');
		if (i < sh->n_pipe)
			pipe(sh->pipe[i].p);
		close_pipes(sh, i, &pi);
		start_cmd(tmp, sh, i, fd_in);
		sh->last_oper = tmp->oper;
		tmp = tmp->next;
		i++;
		if (fd_in)
			close(fd_in);
		fd_in = 0;
	}
	end_fork(sh);
	return (tmp);
}

void	subexec(t_sh *sh, t_cmd *cm, int *pi)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		(void) cm;
		(void) sh;
		close (pi[OUT]);
		dup2(pi[IN], STDOUT_FILENO);
		close (pi[IN]);
		execve(getenv("_"), cm->argvec, environ);
		perror("exc: ");
		ft_exit_fail(sh, NULL);
	}
	close(pi[IN]);
	waitpid(pid, &status, 0);
	sh->last_re = WEXITSTATUS(status);
}

t_cmd	*sub_cat(int *pi, t_cmd *cm)
{
	pid_t	pid;
	char	*arg[2];
	int		status;

	arg[0] = "cat";
	arg[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		ft_sig_cancel();
		close (pi[IN]);
		dup2(pi[OUT], STDIN_FILENO);
		close (pi[OUT]);
		execve("/bin/cat", arg, NULL);
		perror("exc: ");
	}
	waitpid(pid, &status, 0);
	close(pi[OUT]);
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
	int		file;

	i = 0;
	ft_bzero(buf, 9999);
	read(fd_pipe, buf, 10000);
	while (cm->token_tab[i])
	{
		if (cm->token_tab[i]->type == OPER)
			file = open(cm->token_tab[i + 1]->str, O_CREAT | O_RDWR, 0000777);
		if (cm->token_tab[i + 1] == NULL)
			break ;
		i++;
	}
	write(file, buf, ft_strlen(buf));
	close(file);
	return (cm->next);
}
