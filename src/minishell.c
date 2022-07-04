/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/07/04 19:11:25 by agrenon          ###   ########.fr       */
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
			if (sh->token_lst && sh->cmd_lst)
				start_exec(sh);
		}
		free_lst(sh);
		sh->token_lst = NULL;
	}
}

void	start_shell_bonus(t_sh *sh, char **argv)
{
	init_var(sh);
	sh->line = ft_strdup(argv[1]);
	if (sh->line && sh->line[0] != '\0')
	{
		line_parser(sh);
		if (sh->token_lst && sh->cmd_lst)
			start_exec(sh);
	}
	free_lst(sh);
	free_doble_arr(sh->env);
	rl_clear_history();
	free(sh);
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
	return (sh->last_re);
}
