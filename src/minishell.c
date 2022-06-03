#include "minishell.h"

void	free_lst(t_tokens *top)
{
	t_tokens *begin;
	t_tokens *temp;

	begin = top;
	while(begin)
	{
		temp = begin;
		begin = begin->next;
		free (temp);
	}
}

void start_readline(t_sh *sh)
{
		sh->line = readline("miniShell$ ");
		if (sh->line != 0)
			add_history(sh->line);
}

void start_shell(t_sh * sh)
{
	while (1)
	{
		start_readline(sh);
		if (sh->line && sh->line[0] != '\0')
			line_parser(sh);	
		//if (sh->token_top)
		//	check_builtins(sh);
		//exec_cmd(sh);
		start_exec(sh);
		
		free(sh->line);
		free_lst(sh->token_top);
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

