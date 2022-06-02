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

void ft_export(char **s)
{
	int i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	environ[i] = malloc(sizeof(char) * ft_strlen(s[1])); 
	environ[i] = s[1];	
	environ[i + 1] = NULL;
}

void ft_env(void)
{
	int i;

	i = 0;
	while (environ[i] != NULL)
	{
		ft_printf("%s\n", environ[i]);
		i++;
	}
}
