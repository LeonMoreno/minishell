#include "minishell.h"

void start_shell(t_sh *sh)
{
	while (1)
	{
		sh->line = readline("miniShell$ ");
	}
}

int main(void)
{
	t_sh sh;

	start_shell(&sh);
	
	return (0);
}

