#include "minishell.h"

char	**join_path(char **split, char **tab)
{
	int		i;
	char	*temp;
	char	*path;

	path = NULL;
	i = 0;
	while(i < ft_size_arr(split) - 2) 
	{
		if (i == 0)
			temp = ft_strjoin(split[i], "/");
		else
			temp = ft_strjoin(path, "/");
		if (path)
			free(path);
		path = ft_strjoin(temp, split[i + 1]);
		free(temp);
		i++;
	}
	tab[0] = path;
	tab[1] = ft_strdup(split[ft_size_arr(split) - 1]);
	free_doble_arr(split);
	return (tab);
}
char	**str_folder(char *str)
{
	char	**temp;
	char	**tab;

	tab = malloc(sizeof(char *) * 3);
	tab[2] = NULL;
	temp = ft_split(str, '/');
	if (!temp[1])
	{
		tab[0] = ft_strdup(".");
		tab[1] = ft_strdup(temp[0]);
		free_doble_arr(temp);
		return (tab);
	}
	else if (temp[2])
		return (join_path(temp, tab));
	free(tab);
	return (temp);
}

char	**ft_add_argvec(char **argvec, char *wild_str, DIR *d, int len)
{
	struct dirent *dir;
	t_argve		*wild_lst;
	char		**new_argvec;
	int	i;

	wild_lst = NULL;
	while ((dir = readdir(d)))
	{	
		if (ft_is_accepted(wild_str, dir->d_name))
		{
			printf("Arguments from readdir: %s\n", dir->d_name);
			wild_lst = argve_lst(wild_lst, dir->d_name);
		}
	}
	new_argvec = new_argve_tab(argvec, wild_lst, len, wild_str);
	i = 0;
	while (new_argvec[i])
	{
		printf("New Argvec element %d: %s\n", i, new_argvec[i]);
		i++;
	}
	//free_doble_arr(argvec);
	return (new_argvec);
}

char	**openthydir(char **argvec, char *wild_str, int len_argve, int *i)
{
	DIR		*d;
	char	**split;
	char	**new_argvec;
	int		j;

	split = NULL;
	split = str_folder(wild_str);
	d = opendir(split[0]);
	if (!d)
	{
		perror("minishell: ");
		return (0);
	}
	new_argvec = ft_add_argvec(argvec, split[1], d, len_argve);
	j = 0;
	while (new_argvec[j])
		j++;
	*i = j;
	free_doble_arr(split);
	//free_doble_arr(argvec);
	closedir(d);
	return (new_argvec);
}
