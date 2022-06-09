#include "minishell.h"

/**
 * start_pipex - create des pipes
 * @sh->pip : ptr struct s_pip
 */
void	start_pipex(t_sh *sh)
{
	int	i;

	i = 0;
	sh->pipe = malloc(sizeof(t_pip) * sh->n_pipe);
	while (sh->n_pipe > i)
	{
		ft_printf("Entre PIPE %d\n", i);
		pipe(sh->pipe[i++].p);
	}
}

/**
 * init_fork - start and malloc var sh->id_f aka var_forks
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
	sh->id_f = malloc(sizeof(pid_t) * i);
	return (i);
}

/**
 * start_cmd = begin start commands
 * if there pipe are forks builtins exec with in fork
 * if no pipe builtins exec without fork
 */
void	start_cmd(t_cmd *cm, t_sh *sh, int i, int x)
{
	if (!check_cmd(sh->cmd_lst->name) || sh->n_pipe > 0)
	{
		sh->id_f[i] = fork();
		if (sh->id_f[i] == 0)
		{
			if (check_cmd(cm->name))
				start_child_builtins(cm, sh);
			else
				start_child_cmdext(cm, sh, i, x);
		}
	}
	else
	{
		start_builtins(cm, sh);
		printf("EJECUTE cmd = %s PID %d\n", cm->name, getpid());
	}
}

/**
 * start_exec - start fork/pipes/commands/EndForks
 * @i: use for index var sh->id_f: fork
 * @n_f: number of forks
 * @x : index number pipex, increment chaque 2 commands
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
	printf ("n_forks = %d FORKs\n", sh->n_forks);
	end_fork(sh);
}
