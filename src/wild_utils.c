#include "minishell.h"

int	size_alst(t_argve *lst)
{
	int		i;
	t_argve	*begin;

	begin = lst;
	if (!begin)
		return (0);
	i = 0;
	while (begin)
	{
		if (begin->str[0] == '\0')
			break ;
		begin = begin->next;
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
	(void) j;
	(void) i;
	if (wild_str[0] != '.' && (!ft_strncmp(str, ".", 2) || !ft_strncmp(str, "..", 3)))
		return (0);
	if (wild_str[0] != '.' && str[0] == '.')
		return (0);

	if (ft_wild_split_ncmp(wild_str, str))
		return (1);
	return (0);
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
			if (!begin->next)
				break ;
			begin = begin->next;
		}
		begin->next = new_arg;
	}
	return (lst);
}

char	**new_argve_tab(char **argvec, t_argve *lst, int old, char *ws)
{
	int		len;
	char	**new_argvec;
	int		i;
	t_argve *begin;

	len = ft_size_arr(argvec) + size_alst(lst) - 1;
	i = len + old - 1; 
	if (!lst)
		i++;
	new_argvec = malloc(sizeof(char *) * (i + 1));
	printf("new argvec size: %d\n", i + 1);
	ft_argvec_zero(new_argvec, i + 1);
	begin = lst;
	i = 0;
	while (i < ft_size_arr(argvec))//-1)
	{
		new_argvec[i] = ft_strdup(argvec[i]);
		i++;
	}
	while (i < len + 1 && lst)
	{
		if (!begin)
			break ;
		new_argvec[i] = ft_strdup(begin->str);
		begin = begin->next;
		i++;
	}
	if (!lst)
		new_argvec[i++] = ft_strdup(ws);
	new_argvec[i] = NULL;
	return (new_argvec);
}
