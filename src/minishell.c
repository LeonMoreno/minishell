#include "minishell.h"

void	start_readline(t_sh *sh)
{
	sh->promt = ft_strjoin(getenv("USER"), "@miniShell$ ");
	sh->line = readline(sh->promt);
	if (sh->line != 0)
		add_history(sh->line);
	if (sh->line == NULL)
	{
		printf("%s\n", "exit");
		ft_exit(sh);
	}
}

void	start_shell(t_sh *sh)
{
	ft_printf("\n\t\t ** PROC INI PID %d **\n\n", getpid());
	while (1)
	{
		start_readline(sh);
		if (sh->line && sh->line[0] != '\0')
		{
			line_parser(sh);
			if (sh->token_lst)
			{	
//				ft_print_cmds(sh); // Print basic info of all cmds in cmd_lst
				start_exec(sh);
				//printf("APRES EXEC\n");
				free_lst(sh);
			}
		}
		else if (sh->line && sh->line[0] == '\0')
			free(sh->line);
		sh->token_lst = NULL;
	}
}

int	main(void)
{
	t_sh	*sh;

	sh = malloc(sizeof(t_sh));
	ft_sigaction();
	start_shell(sh);
	return (0);
}
