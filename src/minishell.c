#include "minishell.h"

void start_shell(t_sh *sh)
{
	while (1)
	{
		sh->line = readline("miniShell$ ");
		if (sh->line && sh->line[0] != '\0')
			line_parser(sh);		
		if (sh->token_top)
			check_builtins(sh);
		if (sh->line)
			add_history(sh->line);
		//exec_cmd(sh);		
		free_lst(sh);
		sh->token_top = NULL;
	}
}

int main()
{
	t_sh *sh;
// INITIALIZATION D'UN TEST TOKEN
	sh = malloc(sizeof(t_sh));
	start_shell(sh); //fonction shell
	return (0);
}

