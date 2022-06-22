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

void	ft_exit(t_sh *sh)
{
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
		//if (!sh->n_pipe)
		//	write(1, "\e[0;30m\e[47m%\e[0m", 17);
		if (ft_strncmp(s[i], "-n", 3))
			ft_printf("%s", s[i]);
		if (ft_strncmp(s[i], "-n", 3) && s[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (ft_strncmp(s[1], "-n", 3))
		write(1, "\n", 1);
}

void	ft_cd(char **line_split)
{
	if (!line_split[1])
	{
		if (chdir(getenv("HOME")) == -1)
			perror("cd");
	}
	else if (line_split[1][0] == '~')
	{
		if (chdir(getenv("HOME")) == -1)
			perror("cd");
	}
	else if (chdir(line_split[1]) == -1)
		perror("cd");
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
