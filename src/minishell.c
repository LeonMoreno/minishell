#include "minishell.h"

void line_parser(t_sh *sh)
{
	sh->line_split = ft_split(sh->line, ' ');
}

void start_shell(t_sh *sh)
{
	while (1)
	{
		sh->line = readline("miniShell$ ");
		if (sh->line)
			add_history(sh->line);
		line_parser(sh);
		//exec_cmd(sh);
		free(sh->line);
	}
}

int main(void)
{
	t_sh sh;

	start_shell(&sh);
	
	return (0);
}

