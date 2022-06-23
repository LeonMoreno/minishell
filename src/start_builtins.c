/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:25:47 by lmoreno           #+#    #+#             */
/*   Updated: 2022/06/23 12:32:36 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getpwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		perror("pwd ");
	else
	{
		ft_printf("%s\n", buf);
		free(buf);
	}
}

void	ft_exit(t_sh *sh, char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	if (i > 2)
	{
		ft_printf("exit: too many arguments\n");
		return ;
	}
	if (sh->line)
	{
		rl_clear_history();
		free_lst(sh);
		free_doble_arr(sh->env);
	}
	exit (EXIT_SUCCESS);
}

void	ft_echo(char **s)
{
	int	i;

	i = 1;
	if (!s[i])
	{
		write(1, "\n", 1);
		return ;
	}
	while (s[i] != NULL)
	{
		if (ft_strncmp(s[i], "-n", 3))
			ft_printf("%s", s[i]);
		if (ft_strncmp(s[i], "-n", 3) && s[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (ft_strncmp(s[1], "-n", 3))
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
			perror("cd");
	}
	else
	{
		if (chdir(s[1]) == 0)
			ft_export(oldpwd, sh);
		else
			perror("cd");
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
			perror("cd");
	}
	else if (s[1][0] == '~' && s[1][1] == '\0')
	{
		if (chdir(getenv("HOME")) == 0)
			ft_export(oldpwd, sh);
		else
			perror("cd");
	}
	else
		ft_cd_next(s, sh, oldpwd);
	free(buf);
	free(oldpwd);
}
