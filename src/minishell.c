#include "minishell.h"

void	start_readline(t_sh *sh)
{
	char	*str;
	char	*temp;
	char	*final;

	str = NULL;
	str = ft_strjoin(BHGRN, getenv("USER"));
	if (!str)
		str = ft_strjoin(BHGRN, "user");
	temp = ft_strjoin(HRED, "@minishell$ ");
	final = ft_strjoin(temp, RESET);
	free(temp);
	sh->promt = ft_strjoin(str, final);
	free(str);
	free(final);
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
	ft_printf("\n\t\t %s ** PROC INI PID %d ** %s\n\n", UBLU, getpid(), RESET);
	while (1)
	{
		init_var(sh);
		start_readline(sh);
		if (sh->line && sh->line[0] != '\0')
		{
			line_parser(sh);
			if (sh->token_lst) //&& ft_parse_err(sh->token_lst))
			{	
				//ft_print_cmds(sh);//  Print basic info of all cmds in cmd_lst
				start_exec(sh);
				//printf("APRES EXEC\n");
			}
			free_lst(sh);
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
	start_env(sh);
	start_shell(sh);
	return (0);
}
