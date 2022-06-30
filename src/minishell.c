/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@42quebec.com>             +#+  +:+       +#+        */
/*   By: lmoreno <lmoreno@42quebec.com>            +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:36:28 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/23 16:47:38 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_exit(sh, NULL);
	}
}

void	start_shell(t_sh *sh)
{
	ft_printf("\n\t\t %s *** PROC INI PID %d *** %s\n\n", UBLU, getpid(), RESET);
	while (1)
	{
		init_var(sh);
		start_readline(sh);
		if (sh->line && sh->line[0] != '\0')
		{
			line_parser(sh);
			ft_print_cmds(sh);
			if (sh->token_lst && sh->cmd_lst)
				start_exec(sh);
		}
//		free_lst(sh);
		sh->token_lst = NULL;
	}
}

void	start_shell_bonus(t_sh *sh, char **argv)
{
	ft_printf("\n\t\t %s *** BONUS PID %d *** %s\n\n", UBLU, getpid(), RESET);
	init_var(sh);
	sh->line = ft_strdup(argv[1]);
	//start_readline(sh);
	if (sh->line && sh->line[0] != '\0')
	{
		line_parser(sh);
		ft_print_cmds(sh);
		if (sh->token_lst && sh->cmd_lst)
			start_exec(sh);
	}
//	free_lst(sh);
	sh->token_lst = NULL;
}

int	main(int argc, char **argv)
{
	t_sh	*sh;

	sh = malloc(sizeof(t_sh));
	start_env(sh);
	ft_sigaction();
	if (argc == 1)
		start_shell(sh);
	else
		start_shell_bonus(sh, argv);
	return (0);
}
