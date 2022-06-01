#include "minishell.h"

void ft_getpwd(void)
{
	char pwd[100];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}

void ft_exit(char *line)
{
	free(line);
	exit (EXIT_SUCCESS);
}

void ft_echo(char **line_split)
{
	int i;

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

void ft_cd(char **line_split)
{
	if (line_split[1][0] == '~')
	{
		if (chdir(getenv("HOME")) == -1)
			perror("cd");
	}
	else if (chdir(line_split[1]) == -1)
		perror("cd");
}

void ft_export(void)
{
	ft_printf("haciendo EXPORT\n");
	if (setenv("LEOOOOHOEO", "107", 0) != 0)
		perror("setenv");
}

void ft_env(t_sh *sh)
{
	int i;

	i = 0;
	while (sh->envs[i] != NULL)
	{
		ft_printf("%s\n", sh->envs[i]);
		i++;
	}
}
