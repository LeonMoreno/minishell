#include "minishell.h"

void s_parsing_cmd(t_cmd *cm, t_sh *sh)
{
	char *path_all;
	char **path_split;
	char *path;
	char *cmd;
	int	i;

	i = 0;
	cmd = ft_strjoin("/", cm->name);
	printf("IN PARSER CMD = %s  %s\n", cmd, sh->cmd_lst->name);
	path_all = getenv("PATH");
	path_split = ft_split(path_all, ':');
	while (path_split[i] != NULL)
	{
		path = ft_strjoin(path_split[i], cmd);
		if (!access(path, X_OK))
			printf("%s\n", path);
		i++;
	}
}
