#include "minishell.h"

static	void	init_void_env(t_sh *sh, int x)
{
	sh->env = malloc(sizeof(char *) * x + 3);
	sh->env[x] = ft_strdup("HOME=/home");
	sh->env[x + 1] = ft_strdup("USER=user");
	sh->env[x + 2] = NULL;
	environ = sh->env;
}

static	void	init_env(t_sh *sh, int x)
{
	int	i;

	i = 0;
	sh->env = malloc(sizeof(char *) * (x + 1));
	while (environ[i] != NULL)
	{
		sh->env[i] = ft_strdup(environ[i]);
		i++;
	}
	sh->env[i] = NULL;
	environ = sh->env;
}

void	start_env(t_sh *sh)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	if (i > 5)
		init_env(sh, i);
	else
		init_void_env(sh, i);
}
