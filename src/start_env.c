#include "minishell.h"

void	init_env(t_sh *sh, int x)
{
	int	i;

	i = 0;
	sh->env = malloc(sizeof(char *) * x);
	while (environ[i] != NULL)
	{
		sh->env[i] = ft_strdup(environ[i]);
		i++;
	}
	sh->env[i] = NULL;
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
		ft_printf("NO hay ENV\n");
}
