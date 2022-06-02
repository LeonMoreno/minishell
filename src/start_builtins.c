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
	char **new_env;
	char **key_s;
	char **key_env;

	i = 0;
	key_s = ft_split(s[1], '=');
	while (environ[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * i + 2);
	i = 0;
	while (environ[i] != NULL)
	{
		key_env = ft_split(environ[i], '=');
		if(!ft_strncmp(key_s[0], key_env[0], ft_strlen(key_s[0])))
		{
			new_env[i] = malloc(sizeof(char) * ft_strlen(s[1])); 
			new_env[i] = s[1];
		}
		else
		{
			new_env[i] = malloc(sizeof(char) * ft_strlen(environ[i]));
			new_env[i] = environ[i];
		}
		i++;
	}

	new_env[i] = malloc(sizeof(char) * ft_strlen(s[1])); 
	new_env[i] = s[1];	
	new_env[i + 1] = NULL;
	environ = new_env;
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
