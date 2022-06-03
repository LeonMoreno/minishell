#include "minishell.h"

void start_readline(t_sh *sh)
{
		sh->line = readline("miniShell$ ");
		if (sh->line != 0)
			add_history(sh->line);
}

void start_shell(t_sh *sh)
{
	while (1)
	{
		start_readline(sh);
		if (sh->line && sh->line[0] != '\0')
		{
			line_parser(sh);	
			if(sh->token_lst) //If expansion NULL, Token lst is NULL
			{	
				ft_print_cmds(sh); // Print basic info of all cmds in cmd_lst
				start_exec(sh);
				free_lst(sh);
			}
		}
		sh->token_lst = NULL;
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

