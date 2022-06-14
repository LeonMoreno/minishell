#include "minishell.h"

int		ft_end_expansion(t_sh *sh, int i)
{
	while (sh->line[i])
	{
		if (sh->line[i] == 39 || sh->line[i] == 34 || sh->line[i] < 33 )  
			break ;
		if (sh->line[i + 1] == '$')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	*ft_compare_env(t_sh *sh, int start, int end)
{
	char	*expan;
	char	*found;
	
	expan = ft_substr(sh->line, start + 1, end - start - 1);
	found = getenv(expan);
	if (found)
		found = ft_strdup(found);
	return (found);
}

char	*ft_expansion(t_sh *sh, int *i, char *temp)
{
	int		end;
	char	*new_temp;
	char	*found;
	
	end = ft_end_expansion(sh, *i);
	//printf("END: %d CHAR: %c\n", end, sh->line[end]);
	found = ft_compare_env(sh, *i, end);
	*i = end - 1;
	if (temp && found)
		new_temp = ft_strjoin(temp, found);
	else if (!found)
		return (temp);
	else
		return (found);
	free(temp);
	free(found);
	return (new_temp);
}
