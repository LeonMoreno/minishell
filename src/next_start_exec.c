/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_start_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:12:05 by lmoreno           #+#    #+#             */
/*   Updated: 2022/07/04 19:15:51 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*path;
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		(void) cm;
		(void) sh;
		path = getenv("PWD");
		path = ft_strjoin(path, "/minishell");
		printf("shell = %s\n", path);
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
	pid_t	pid;
	char	*arg[2];

	arg[0] = "cat";
	arg[1] = NULL;
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
	return (cm->next);
}
