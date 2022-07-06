/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:25:47 by lmoreno           #+#    #+#             */
/*   Updated: 2022/07/06 12:24:12 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_arg_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	msg_exit(char **argv)
{
	if (argv)
		ft_printf("exit\n");
}

void	ft_exit(t_sh *sh, char **argv)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (argv && argv[i])
		i++;
	if (argv && argv[1] && ft_arg_valid(argv[1]) && i > 2)
	{
		ft_printf("miniShell: exit too many arguments\n");
		return ;
	}
	if (argv && argv[1] && !ft_arg_valid(argv[1]))
		ft_printf("miniShell: exit: %s: numeric argument required\n", argv[1]);
	if (argv && argv[1])
		e = ft_atoi(argv[1]);
	msg_exit(argv);
	if (sh->line)
	{
		free_lst(sh);
		free_doble_arr(sh->env);
	}
	rl_clear_history();
	free(sh);
	exit (e);
}

void	ft_cd_next(char **s, t_sh *sh, char *oldpwd)
{
	if (s[1][0] == '~' && s[1][1] == '/')
		ft_cd_home_relativo(s, sh, oldpwd);
	else if (s[1][0] == '-')
	{
		if (chdir(getenv("OLDPWD")) == 0)
			ft_export(oldpwd, sh);
		else
			ft_perror("cd", sh);
	}
	else
	{
		if (chdir(s[1]) == 0)
			ft_export(oldpwd, sh);
		else
			ft_perror("cd", sh);
	}
}

void	ft_cd(char **s, t_sh *sh)
{
	char	*buf;
	char	*oldpwd;

	buf = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", buf);
	if (!s[1])
	{
		if (chdir(getenv("HOME")) == 0)
			ft_export(oldpwd, sh);
		else
			ft_perror("cd", sh);
	}
	else if (s[1][0] == '~' && s[1][1] == '\0')
	{
		if (chdir(getenv("HOME")) == 0)
			ft_export(oldpwd, sh);
		else
			ft_perror("cd", sh);
	}
	else
		ft_cd_next(s, sh, oldpwd);
	free(buf);
	free(oldpwd);
}
