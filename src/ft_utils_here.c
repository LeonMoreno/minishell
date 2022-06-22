#include "minishell.h"

void	child_here(int *i_pipe, t_sh *sh, char *operand)
{
	char	*temp;

	close(i_pipe[0]);
	temp = ft_heredoc(operand, sh);
	write(i_pipe[1], temp, ft_strlen(temp));
	close(i_pipe[1]);
	free_lst(sh);
	exit(0);
}
