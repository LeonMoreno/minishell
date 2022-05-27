#include "minishell.h"

void start_shell(t_sh *sh)
{
	while (1)
	{
		sh->line = readline("miniShell$ ");
		if (!(ft_strncmp(sh->line, "exit", 5)))
					break;
		free(sh->line);
	}
}

int main(void)
{
	t_sh sh;

	start_shell(&sh);
	
	return (0);
}

