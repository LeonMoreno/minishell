#include "minishell.h"

void	ft_unset_next(char **s, char **new_env)
{
	int		i;
	int		j;
	char	**key_env;

	i = 0;
	j = 0;
	while (environ[i] != NULL)
	{
		key_env = ft_split(environ[i], '=');
		if (ft_strncmp(s[1], key_env[0], ft_strlen(s[1] + 1)))
		{
			new_env[j] = malloc(sizeof(char) * ft_strlen(environ[i]));
			new_env[j] = environ[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	//free(environ);
	environ = new_env;
}

void	ft_unset(char **s)
{
	int		i;
	char	**new_env;

	i = 0;
	if (!s[1])
	{
		ft_printf("unset: not enough arguments\n");
		return ;
	}
	while (environ[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * i + 1);
	ft_unset_next(s, new_env);
}

/**
 * @brief ft_export: malloc un nuevo espacio de mem para new env
 * y agrego nueva variable, comparando si ya existe o 
 * si no la meto a lo ultimo. 
 * 1 - Si no hay argumento llamo ft_env() - imprimo env
 * Por ultimo la muevo el ptr de environ al nuevo array.
 * *
 * @key_s: split argu export avec = (leo=uno)
 * @**new_env: Nuevo array 
 * @**key_s argu de export
 * @**key_env variable de environ donde comparo si existe la variable (leo)
 */

int	sch(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}


void	ft_export_last(int ctrl, int i, char **s, char **new_env)
{
	static	int x = 1;

	printf("TERCER FC i = %d\n", i);
	if (!ctrl)
		new_env[i] = ft_strdup(s[1]);
	new_env[i + 1] = NULL;
	if (x > 1)
	{
		printf("x = %d\n", x);
		free_doble_ptr(environ);
	}
	x++;
	//free(environ);
	environ = new_env;
	printf("Awui LLEGO\n");
}

void	ft_export_next(char **new_env, char **key_s, char **s)
{
	int		i;
	int		ctrl;

	i = 0;
	ctrl = 0;
	while (environ[i] != NULL)
	{
		if (!ft_strncmp(environ[i], key_s[0], sch(environ[i], '=')))
		{
			printf("ENtre %s env = %s\n", s[1], environ[i]);
			new_env[i] = ft_strdup(s[1]);
			printf("NEW_ENV = %s\n", new_env[i]);
			ctrl = 1;
		}
		else
		{
			new_env[i] = malloc(sizeof(char) * ft_strlen(environ[i]));
			new_env[i] = ft_memcpy(new_env[i], environ[i], ft_strlen(environ[i]));
			//new_env[i] = ft_strdup(environ[i]);
		}
		i++;
	}
//	printf("SEGUNDO WHILL\n");
	//free_doble_ptr(key_s);
		ft_export_last(ctrl, i, s, new_env);
}

void	ft_export(char **s)
{
	int		i;
	char	**new_env;
	char	**key_s;

	i = 0;
	if (!s[1])
	{
		ft_env();
		return ;
	}
	key_s = ft_split(s[1], '=');
	if (!key_s[1])
	{
		printf("AQUI key_s = %s\n", key_s[1]);
		return ;
	}
	while (environ[i] != NULL)
		i++;
	printf("i = %d y ENV = %s\n", i, environ[i]);
	new_env = malloc(sizeof(char *) * i + 1);
	if (!new_env)
	{
		printf("error malloc\n");
		return ;
	}

	ft_export_next(new_env, key_s, s);
}
