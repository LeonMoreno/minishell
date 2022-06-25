#include "minishell.h"

int	size_alst(t_argve *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	check_wild(char *str)
{
	int i;

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

int		ft_is_accepted(char *wild_str, char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		while (wild_str[i] == '*' && wild_str[i + 1] == '*')
			j++;
		if (wild_str[j] != '*' && str[i] != wild_str[j])
			return (0);
		if (wild_str[j] == '*' && str[i] == wild_str[j + 1] && str[i])
			j++;
		else if (wild_str[j] == str[i])
			j++;
		printf("CHAR WILD: %c CHAR str: %c\n", wild_str[j], str[i]); 
		i++;
	}
	return (1);
}

t_argve	*argve_lst(t_argve *lst, char *str)
{
	t_argve	*new_arg;
	t_argve	*begin;

	new_arg = malloc(sizeof(t_argve));
	new_arg->next = NULL;
	new_arg->str = ft_strdup(str);
	if (!lst)
		lst = new_arg;
	else
	{
		begin = lst;
		while (begin)
		{
			printf("Argve list str-> %s\n", begin->str);
			if (!begin->next)
				break ;
			begin = begin->next;
		}
		begin->next = new_arg;
	}
	return (lst);
}

char	**new_argve_tab(char **argvec, t_argve *lst)
{
	int	len;
	char	**new_argvec;
	int		i;

	i = 0;
	len = ft_size_arr(argvec) + size_alst(lst);
	printf("len: %d\n", len);
	new_argvec = malloc(sizeof(char *) * (len + 1));
	new_argvec[len] = NULL;
	while (i < ft_size_arr(argvec))
	{
		new_argvec[i] = ft_strdup(argvec[i]);
		printf("ancient argve: %s\n", new_argvec[i]);
		i++;
	}
	//free_doble_arr(argvec);
	while (i < len)
	{
		if (!lst)
			break ;
		if (lst->str)
			new_argvec[i] = ft_strdup(lst->str);
		printf("list str: %s\n", new_argvec[i++]);
		lst = lst->next;
		i++;
	}
	return (new_argvec);
}
