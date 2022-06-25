#include "minishell.h"
/*
int	check_wild(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
*/
char	**join_path(char **split, char **tab)
{
	int		i;
	char	*temp;
	char	*path;

	path = NULL;
	i = 0;
	printf("Size arr: %d %s\n", ft_size_arr(split), split[ft_size_arr(split) - 1]);
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
	tab[1] = split[ft_size_arr(split) - 1];
	free_doble_arr(split);
	printf("split 1: %s splif 2: %s\n", tab[0], tab[1]);
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
		printf("1 lvl wild");
		tab[0] = ft_strdup(".");
		tab[1] = temp[0];
		free_doble_arr(temp);
		return (tab);
	}
	else if (temp[2])
	{
		printf("many lvl wild");
		return (join_path(temp, tab));
	}
	printf("2 lvl wild");
	free(tab);
	return (temp);
}

void	ft_add_argvec(char **argvec, char *wild_str, DIR *d)
{
	(void)wild_str;
	struct dirent *dir;
	t_argve		*wild_lst;
	char		**new_argvec;
	int			i;

	wild_lst = NULL;
	while ((dir = readdir(d)))
	{	
		//if (ft_is_accepted(wild_str, dir->d_name))
			wild_lst = argve_lst(wild_lst, dir->d_name);
	}
	new_argvec = new_argve_tab(argvec, wild_lst);
	i = 0;
	while (new_argvec[i])
	{
		printf("argvec : %s\n", new_argvec[i]);
		i++;
	}

}

int	openthydir(char **argvec, char *wild_str)
{
	DIR *d;
	char	**split;

	split = NULL;
	split = str_folder(wild_str);
	if (split[0][0])
		d = opendir(split[0]);
	else
		d = opendir(".");
	if (!d)
	{
		perror("minishell: ");
		return (0);
	}
	ft_add_argvec(argvec, split[1], d);
	closedir(d);
	return (0);
}
