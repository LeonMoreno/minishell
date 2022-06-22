#include "minishell.h"

void	init_var(t_sh *sh)
{
	sh->id_f = 0;
	sh->n_cmd = 0;
	sh->n_pipe = 0;
	sh->n_forks = 0;
	sh->n_tokens = 0;
	sh->start = 0;
	sh->tmp = NULL;
	sh->token_lst = NULL;
	sh->cmd_lst = NULL;
	sh->line = NULL;
}

static	void	init_void_env(t_sh *sh, int x)
{
	char	*s;

	s = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	sh->env = malloc(sizeof(char *) * (x + 5));
	sh->env[x] = ft_strdup("HOME=/home");
	sh->env[x + 1] = ft_strdup("USER=user");
	sh->env[x + 2] = s;
	sh->env[x + 3] = ft_strdup("SHLVL=1");
	sh->env[x + 4] = NULL;
	environ = sh->env;
}

// Incrémente le niveau du shell
static	char	*init_shlvl(char *shlvl)
{
	char	**tab;
	int		lvl;
	char	*temp;
	char	*chiffre;

	tab = ft_split(shlvl, '=');
	lvl = ft_atoi(tab[1]);
	lvl++;
	chiffre = ft_itoa(lvl);
	temp = ft_strjoin("SHLVL=", chiffre);
	free(chiffre);
	free_doble_arr(tab);
	return (temp);
}

static	void	init_env(t_sh *sh, int x)
{
	int	i;

	i = 0;
	sh->env = malloc(sizeof(char *) * (x + 1));
	while (environ[i] != NULL)
	{
		if (!ft_strncmp(environ[i], "SHLVL", 5))
			sh->env[i] = init_shlvl(environ[i]);
		else
			sh->env[i] = ft_strdup(environ[i]);
		i++;
	}
	sh->env[i] = NULL;
	environ = sh->env;
	sh->last_re = 0;
}

void	start_env(t_sh *sh)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	if (i > 2)
		init_env(sh, i);
	else
		init_void_env(sh, i);
}
