#include "minishell.h"

/**
 * @brief: create des pipes
 * @sh->pip : ptr struct s_pip
 */
void	start_pipex(t_sh *sh)
{
	int	i;

	i = 0;
	if (sh->n_pipe)
	{
		sh->pipe = malloc(sizeof(t_pip) * sh->n_pipe);
		while (sh->n_pipe > i)
			pipe(sh->pipe[i++].p);
	}
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
	printf(" i = %d\n", i);
	if (i > 0)
		sh->id_f = malloc(sizeof(pid_t) * i);
	//if (!sh->id_f)
	//	exit(1);	
	return (i);
}

/**
 * @brief: begin start commands extern & builtins
 * if there pipe || are builtins exec builtins with in fork
 * if no pipe builtins exec without fork
 * if cmd has a fd_in , Dup2 stdin 
 */
void	start_cmd(t_cmd *cm, t_sh *sh, int i, int x)
{
	
	if (!check_cmd(sh->cmd_lst->name) || sh->n_pipe > 0)
	{
		sh->id_f[i] = fork();

		if (sh->id_f[i] == 0)
		{
			//printf("Child before dup cm->fd_in : %d\n", cm->fd_in);
			if (cm->fdin_str)
			{
				close(cm->fd_in);
				cm->fd_in = open(cm->fdin_str, O_RDONLY, 777);
			}
			if (cm->fd_in > 2)
				dup2(cm->fd_in, 0);
			
			if (check_cmd(cm->name) && cm->fd_in != -1)
				start_child_builtins(cm, sh, x);
			else if (cm->fd_in != -1)
				start_child_cmdext(cm, sh, i, x);
			exit(0);
		}
	}
	else
		start_builtins(cm, sh);	
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
	int		x;

	i = 0;
	x = 0;
	cm = sh->cmd_lst;
	start_pipex(sh);
	sh->n_forks = init_fork(sh);
	while (cm)
	{
		if (i != 0 && i % 2 == 0)
			x++;
		start_cmd(cm, sh, i, x);
		cm = cm->next;
		i++;
	}
	end_fork(sh);
}
