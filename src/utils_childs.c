/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:25:01 by lmoreno           #+#    #+#             */
/*   Updated: 2022/07/07 15:38:11 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/**
 * @brief: cambio stdOUT CMD envio info al IN DEL PIPE_i
 * @i: numero del PIPE, q es el mismo No del fork
 **/
void	dup_stdout(t_sh *sh, int i)
{
	close(sh->pipe[i].p[OUT]);
	dup2(sh->pipe[i].p[IN], STDOUT_FILENO);
	close(sh->pipe[i].p[IN]);
}

/**
 * @brief: cambio stdIN CMD tomo info DEL OUT PIPE_i
 * @i: numero del PIPE, q es el mismo No del fork
 **/
void	dup_stdin(t_sh *sh, int i)
{
	close(sh->pipe[i - 1].p[IN]);
	dup2(sh->pipe[i - 1].p[OUT], STDIN_FILENO);
	close(sh->pipe[i - 1].p[OUT]);
}

/**
 * end_fork - if we are fork - wait childs exit
 * @status: save status child
 * @n_f: number of forks
 *
 */
void	end_fork(t_sh *sh)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	j = 0;
	while (i < sh->n_forks)
	{
		ft_silence();
		waitpid(sh->id_f[i++], &status, 0);
		ft_sigaction();
		if (sh->pipe && (j < sh->n_pipe))
		{
			close(sh->pipe[j].p[OUT]);
			close(sh->pipe[j++].p[IN]);
		}
	}
	if (sh->n_forks)
	{
		sh->last_re = WEXITSTATUS(status);
		free(sh->id_f);
		sh->id_f = NULL;
	}
	if (sh->pipe)
		free(sh->pipe);
}

void	ft_exit_fail(t_sh *sh, char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	if (i > 2)
	{
		ft_printf("exit: too many arguments\n");
		return ;
	}
	if (sh->line)
	{
		free_lst(sh);
		free_doble_arr(sh->env);
	}
	rl_clear_history();
	free(sh);
	exit (EXIT_FAILURE);
}
