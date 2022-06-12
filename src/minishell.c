#include "minishell.h"

void start_readline(t_sh *sh)
{
	char *promt;

	promt = malloc(sizeof(char) * ft_strlen(getenv("USER")) + 12);
	promt = ft_strjoin(getenv("USER"), "@miniShell$ ");

		sh->line = readline(promt);
		if (sh->line != 0)
			add_history(sh->line);
}

void	handle_signals(int s)
{
	if (s == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	impri_argv(t_sh *sh)
{
	t_tokens **c;
	int		i;

	i = 0;
	c = sh->cmd_lst->token_tab;
	while (c[i])
	{
		printf("i = %d = %s\n", i, c[i]->str);
		i++;
	}
}

void start_shell(t_sh *sh)
{
	ft_printf("\n\t\t ** PROC INI PID %d **\n\n", getpid());
	while (1)
	{
		start_readline(sh); // FT ReadLine
		if (sh->line && sh->line[0] != '\0')
		{
			line_parser(sh);	
			if(sh->token_lst) //If expansion NULL, Token lst is NULL
			{	
				//ft_print_cmds(sh); // Print basic info of all cmds in cmd_lst
				//impri_argv(sh);
				//ft_print_cmds(sh);
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
	signal(SIGINT, handle_signals);
	start_shell(sh); //fonction shell
	return (0);
}

