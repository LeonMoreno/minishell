/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3buil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 19:33:10 by lmoreno           #+#    #+#             */
/*   Updated: 2022/07/06 15:38:56 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_export(int f, char **s, t_sh *sh)
{
	int	i;

	i = 1;
	if (!s[i] && f == 0)
	{
		ft_env(sh);
		return ;
	}
	while (s[i])
	{
		if (f == 0)
			ft_export(s[i], sh);
		if (f == 1)
			ft_unset(s[i], sh);
		i++;
	}
}

void	ft_getpwd(t_sh *sh)
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
	sh->last_re = 0;
}

void	ft_export_pwd(t_sh *sh)
{
	char	*buf;
	char	*pwd;

	buf = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", buf);
	ft_export(pwd, sh);
	free(buf);
	free(pwd);
}

int	ft_chr_n(char *s, int *ctr, t_sh *sh)
{
	int	i;

	i = 1;
	sh->last_re = 0;
	if (s[i] == '\0')
		return (1);
	while (s[i])
	{
		if (s[i] != 'n')
			return (1);
		i++;
	}
	*ctr = *ctr + 1;
	return (0);
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
