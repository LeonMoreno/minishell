#include "minishell.h"

void	start_redir_fork(t_cmd *cm, t_sh *sh)
{
	printf("i = %d \n", sh->n_forks);
	//if (sh->n_forks == 1)
		start_redir(cm);
}

void	start_redir(t_cmd *cm)
{
	t_tokens	**t;
	int			i;
	int			j;

	t = cm->token_tab;
	i = 0;
	j = 0;
	cm->fds = malloc(sizeof(int) * cm->n_redir);
	if (!cm->fds)
		exit (1);
	while (t[i])
	{
		if (!ft_strncmp(t[i]->str, ">", 2) || !ft_strncmp(t[i]->str, "<", 2))
		{
			cm->fds[j] = open(t[i + 1]->str, O_CREAT | O_RDWR, 0000644);
			j++;
		}
		i++;
	}
	dup2(cm->fds[j - 1], STDOUT_FILENO);
}

void	close_redir_buil(t_sh *sh, t_cmd *cm)
{
	int	j;

	j = 0;
	dup2(sh->s_fd, STDOUT_FILENO);
	while (cm->fds[j])
	{
		close(cm->fds[j]);
		j++;
	}
	close(sh->s_fd);
	free(cm->fds);
}
