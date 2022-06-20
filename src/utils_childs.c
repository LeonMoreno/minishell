#include "minishell.h"

void	dup_stdout(t_sh *sh, int x)
{
	close(sh->pipe[x].p[OUT]);
	dup2(sh->pipe[x].p[IN], STDOUT_FILENO);
	close(sh->pipe[x].p[IN]);
}

void	dup_stdout_un(t_sh *sh, int x)
{
	printf("STD_OUT_UN X = %d\n", x);
	close(sh->pipe[x + 1].p[OUT]);
	dup2(sh->pipe[x + 1].p[IN], STDOUT_FILENO);
	close(sh->pipe[x + 1].p[IN]);
}

void	dup_stdin(t_sh *sh, int x)
{
	close(sh->pipe[x].p[IN]);
	dup2(sh->pipe[x].p[OUT], STDIN_FILENO);
	close(sh->pipe[x].p[OUT]);
	printf("SEG_CMD LEi STDIN Voy POR AQUI X = %d\n", x);
}

void	dup_stdin_un(t_sh *sh, int x)
{
	close(sh->pipe[x + 1].p[IN]);
	dup2(sh->pipe[x +1].p[OUT], STDIN_FILENO);
	close(sh->pipe[x +1].p[OUT]);
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
		if (j < sh->n_pipe)
		{
			close(sh->pipe[j].p[OUT]);
			close(sh->pipe[j].p[IN]);
			printf("Close pipe %d\n", j);
			j++;
		}
		waitpid(sh->id_f[i], &status, 0);
		printf("Close CHILD-%d\n", i);
		i++;
	}
	if (sh->id_f)
		free(sh->id_f);
	if (sh->n_pipe)
		free(sh->pipe);
}
