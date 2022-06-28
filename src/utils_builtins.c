/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:25:29 by lmoreno           #+#    #+#             */
/*   Updated: 2022/06/28 14:41:41 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check if cmd is builtins cmd
 *
 * @param s
 * @return 1 if cmd is builtins
 */
int	check_cmd(char *s)
{
	if (!s)
	{
		printf("cmd name = %s\n", s);
		return (0);
	}
	if (!ft_strncmp(s, "exit", 5))
		return (1);
	if (!ft_strncmp(s, "pwd", 4))
		return (1);
	if (!ft_strncmp(s, "cd", 3))
		return (1);
	if (!ft_strncmp(s, "export", 7))
		return (1);
	if (!ft_strncmp(s, "env", 4))
		return (1);
	if (!ft_strncmp(s, "unset", 5))
		return (1);
	if (!ft_strncmp(s, "echo", 5))
		return (1);
	return (0);
}

/**
 * @brief cherche and execute the builtins
 * cherche with strncmp one space the plus in final
 *
 * @param cm struct info cmd
 */
void	start_builtins(t_cmd *cm, t_sh *sh)
{
	char	**argv;

	argv = cm->argvec;
	if (cm->n_r_out > 0)
	{
		sh->true_fd_out = dup(STDOUT_FILENO);
		start_redir(cm);
	}
	if (!ft_strncmp(cm->name, "exit", 5))
		ft_exit(sh, argv);
	else if (argv[0] && !ft_strncmp(argv[0], "pwd", 4))
		ft_getpwd();
	else if (argv[0] && !ft_strncmp(argv[0], "echo", 5))
		ft_echo(argv);
	else if (argv[0] && !ft_strncmp(argv[0], "cd", 3))
		ft_cd(argv, sh);
	else if (argv[0] && !ft_strncmp(argv[0], "export", 7))
		ft_export(argv[1], sh);
	else if (argv[0] && !ft_strncmp(argv[0], "env", 4))
		ft_env();
	else if (argv[0] && !ft_strncmp(argv[0], "unset", 5))
		ft_unset(argv, sh);
	if (cm->n_r_out > 0 && sh->n_forks == 0)
		close_redir_buil(sh, cm);
}

/**
 * @brief Calculo tamano de ENV, dependiendo si hay o no new elements
 *
 * @param key_s: name string variable environ name=var
 * @return int: tamano de ENV.
 */
int	ft_len_env(char *key_s, t_sh *sh)
{
	int		i;
	int		len;
	int		ctrl;
	char	**key_env;

	i = 0;
	ctrl = 0;
	len = 0;
	while (sh->env[len] != NULL)
		len++;
	while (sh->env[i] != NULL)
	{
		key_env = ft_split(sh->env[i], '=');
		if (!ft_strncmp(key_s, key_env[0], ft_strlen(key_s) + 1))
		{
			ctrl = 0;
			free_doble_arr(key_env);
			break ;
		}
		else
			ctrl = 1;
		free_doble_arr(key_env);
		i++;
	}
	return (len = ctrl + len);
}

/**
 * @brief printf env
 *
 */
void	ft_env(void)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		ft_printf("%s\n", environ[i]);
		i++;
	}
}

void	ft_cd_home_relativo(char **s, t_sh *sh, char *oldpwd)
{
	char	*h_rel;
	char	*tmp;

	h_rel = NULL;
	tmp = NULL;
	h_rel = ft_substr(s[1], 1, (ft_strlen(s[1]) - 1));
	tmp = ft_strjoin(getenv("HOME"), h_rel);
	if (chdir(tmp) == 0)
		ft_export(oldpwd, sh);
	else
		perror("cd");
	free(tmp);
	free(h_rel);
}
