#include "minishell.h"

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

/**
 * @brief: begin start commands extern & builtins
 * if there pipe || are builtins exec builtins with in fork
 * if no pipe builtins exec without fork
 * if cmd has a fd_in , Dup2 stdin 
 */
void	start_cmd(t_cmd *cm, t_sh *sh, int i)
{
	if (!check_cmd(sh->cmd_lst->name) || sh->n_pipe > 0)
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

/**
 * @brief: start fork/pipes/commands/EndForks
 * @i: use for index var sh->id_f: fork
 * @n_f: number of forks
 * @x: index number pipex, increment chaque 2 commands
 */
void	start_exec(t_sh *sh)
{
	t_cmd	*cm;
	int		i;
	int		pi;

	i = 0;
	pi = 0;
	cm = sh->cmd_lst;
	start_pipex(sh);
	sh->n_forks = init_fork(sh);
	while (cm)
	{
		chr_redir_out(cm, '>');
		if (i < sh->n_pipe)
			pipe(sh->pipe[i].p);
		close_pipes(sh, i, &pi);
		start_cmd(cm, sh, i);
		cm = cm->next;
		i++;
	}
	end_fork(sh);
}
