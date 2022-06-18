#include "minishell.h"

int	ft_len_env(char *key_s, t_sh *sh)
{
	int		i;
	int		len;
	int		ctrl;
	char		**key_env;

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
			break;
		}
		else
			ctrl = 1;
		free_doble_arr(key_env);
		i++;
	}
	len = ctrl + len;
	return (len);
}

void	ft_unset_next(char **s, char **new_env, t_sh *sh)
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
			new_env[j] = ft_strdup(environ[i]); 
			j++;
		}
		free_doble_arr(key_env);
		i++;
	}
	new_env[j] = NULL;
	free_doble_arr(sh->env);
	sh->env = new_env;
	environ = new_env;
}

void	ft_unset(char **s, t_sh *sh)
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
	new_env = malloc(sizeof(char *) * (i + 1));
	ft_unset_next(s, new_env, sh);
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
void	ft_export_last(int ctrl, int i, char **s, char **new_env, t_sh *sh)
{
	if (!ctrl)
	{
		new_env[i] = ft_strdup(s[1]); 
		new_env[i + 1] = NULL;
	}
	else
		new_env[i] = NULL;
	free_doble_arr(sh->env);
	sh->env = new_env;
	environ = sh->env;
}
/**
 * @brief:
 * @new_env - malloc temp
 * @s export + argu
 * @key_s: split de s
 * @key_env: var de env -- var=argu -- comparo var 
 */
void	ft_export_next(char **new_env, char **key_s, char **s, t_sh *sh)
{
	int		i;
	int		ctrl;
	char	**key_env;

	i = 0;
	ctrl = 0;
	while (sh->env[i] != NULL)
	{
		key_env = ft_split(sh->env[i], '=');
		if (!ft_strncmp(key_s[0], key_env[0], ft_strlen(key_s[0]) + 1))
		{
			new_env[i] = ft_strdup(s[1]); 
			ctrl = 1;
		}
		else
			new_env[i] = ft_strdup(sh->env[i]); 
		free_doble_arr(key_env);
		i++;
	}
	free_doble_arr(key_s);
	ft_export_last(ctrl, i, s, new_env, sh);
}

/**
 *@brief
 *@s: cmd export + argu
 * si no hay argu exec ft_env
 */
void	ft_export(t_sh *sh)
{
	int		len;
	char	**new_env;
	char	**key_s;
	char	**s;

	s = sh->cmd_lst->argvec;
	if (!s[1])
	{
		ft_env();
		return ;
	}
	key_s = ft_split(s[1], '=');
	if (!key_s[1])
		return ;
	len = ft_len_env(key_s[0], sh);
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
	{
		printf("error malloc\n");
		return ;
	}
	ft_export_next(new_env, key_s, s, sh);
}
