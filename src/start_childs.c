/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:25:44 by lmoreno           #+#    #+#             */
/*   Updated: 2022/06/27 20:49:40 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief get variable PATH the env  -- split --
 * cherche than chaque line path+name_cmd
 *
 * @param cm struct with the info the cmd
 * @return char* path if le cmd is trouve if not NULL
 */
char	*cmd_path(t_cmd *cm)
{
	char	**path_split;
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	if (!access(cm->name, X_OK))
		return (cm->name);
	cmd = ft_strjoin("/", cm->name);
	path_split = ft_split(getenv("PATH"), ':');
	if (!path_split)
		return (NULL);
	while (path_split[i] != NULL)
	{
		path = ft_strjoin(path_split[i], cmd);
		if (!access(path, X_OK))
			return (path);
		free(path);
		i++;
	}
	free_doble_arr(path_split);
	free(cmd);
	return (NULL);
}

/**
 * @brief execution commands builtins than fork
 *
 * @param cm struct info cmd
 * @param x index pour le pipex
 */
void	start_child_builtins(t_cmd *cm, t_sh *sh, int i)
{
	dup_stdout(sh, i);
	start_builtins(cm, sh);
	exit (0);
}

void	start_child_next(t_cmd *cm, t_sh *sh)
{
	char	*path;

	if (cm->n_r_out > 0)
		start_redir_fork(cm, sh);
	if (cm->name)
	{
		printf("last_oper exit = %d last_re = %d\n", sh->last_oper, sh->last_re);
		if (sh->last_oper == 5 && sh->last_re != 0)
			ft_exit(sh, cm->argvec);
		path = cmd_path(cm);
		if (!path)
			msg_stderr("miniShell: command not found: ", cm);
		execve(path, cm->argvec, environ);
		perror("execve");
	}
}

/**
 * @brief: execution the commands extern than fork
 * 1) check path if cmd exist. 2) execute selon ordre
 *
 * @param cm: struct with command and argus
 * @param i: index of interactions the forks --
 * 1er_cmd i == 0, last_cmd i + 1 == n_forks(number of forks)
 * @param x: index pour le pipex
 */
void	start_child_cmdext(t_cmd *cm, t_sh *sh, int i)
{
	ft_sig_cancel();
	//printf("CMName = %s Oper = %d pipe = %d redir = %d\n", cm->name, cm->oper, sh->n_pipe, cm->n_r_out);
	if (cm->name)
	{
		if (!check_cmd(sh->cmd_lst->name) && sh->n_pipe > 0 && (i == 0))
			dup_stdout(sh, i);
		else if (sh->n_pipe && sh->n_forks != (i + 1))
		{
			if (!cm->fd_in)
				dup_stdin(sh, i);
			dup_stdout(sh, i);
		}
		else if (!cm->fd_in && sh->n_pipe && sh->n_forks == (i + 1))
			dup_stdin(sh, i);
	}
	start_child_next(cm, sh);
	ft_exit(sh, cm->argvec);
}
