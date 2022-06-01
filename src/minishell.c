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
		if (sh)
			add_history(sh->line);
		line_parser(sh);
		//exec_cmd(sh);
		free(sh->line);
	}
}

int main(int argc, char **argv, char **env)
{
	t_sh sh;

	argc = 0;
	argv = NULL;
	sh.envs = env;

	start_shell(&sh);
	
	return (0);
}

