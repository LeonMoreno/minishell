/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:25:47 by lmoreno           #+#    #+#             */
/*   Updated: 2022/07/04 19:42:23 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_printf("exit\n");
	if (sh->line)
	{
		free_lst(sh);
		free_doble_arr(sh->env);
	}
	rl_clear_history();
	free(sh);
	exit (e);
}

void	ft_echo(char **s, t_sh *sh)
{
	int		i;
	int		ctr;
	bool	skip;

	skip = true;
	ctr = 0;
	i = 1;
	if (!s[i])
	{
		write(1, "\n", 1);
		return ;
	}
	while (s[i] != NULL)
	{
		if (!skip || ft_chr_n(s[i], &ctr, sh))
		{
			ft_printf("%s", s[i]);
			if (s[i + 1] != NULL)
				ft_printf(" ");
			skip = false;
		}
		i++;
	}
	if (ft_strncmp(s[1], "-n", 3) && ctr == 0)
		write(1, "\n", 1);
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
