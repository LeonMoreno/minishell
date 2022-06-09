#include "minishell.h"

char	*cmd_path(t_cmd *cm)
{
	char **path_split;
	char *path;
	char *cmd;
	int	i;

	i = 0;
	cmd = ft_strjoin("/", cm->name);
	path_split = ft_split(getenv("PATH"), ':');
	while (path_split[i] != NULL)
	{
		path = ft_strjoin(path_split[i], cmd);
		if (!access(path, X_OK))
			return (path);	
		free(path);
		i++;
	}
	free(path_split);
	return (NULL);
}
