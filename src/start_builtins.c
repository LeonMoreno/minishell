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

void	ft_exit(char *line)
{
	free(line);
	exit (EXIT_SUCCESS);
}

void	ft_echo(char **line_split)
{
	int	i;

	i = 1;
	while (line_split[i] != NULL)
	{
		ft_printf("%s", line_split[i]);
		if (line_split[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	write(1, "%", 1);
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
