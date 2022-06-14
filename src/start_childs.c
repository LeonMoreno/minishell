#include "minishell.h"

/**
 * @brief get variable PATH the env  -- split -- cherche than chaque line path+name_cmd
 *
 * @param cm struct with the info the cmd
 * @return char* path if le cmd is trouve if not NULL
 */
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

/**
 * @brief execution commands intern than fork
 *
 * @param cm struct info cmd
 * @param x index pour le pipex
 */
void	start_child_builtins(t_cmd *cm, t_sh *sh, int x)
{
//	printf("FORK CMD builtins %s PID %d\n", cm->name, getpid());

	dup_stdout(sh, x);
	start_builtins(cm, sh);
	exit (0);
}

/**
 * @brief: execution the commands extern than fork 1) check path if cmd exist. 2) execute selon ordre
 *
 * @param cm: struct with command and argus
 * @param i: index of interactions the forks -- 1er_cmd i == 0, last_cmd i + 1 == n_forks(number of forks)
 * @param x: index pour le pipex
 */
void	start_child_cmdext(t_cmd *cm, t_sh *sh, int i, int x)
{
	char	*path;

	path = cmd_path(cm);
	if (!path)
		msg_stderr("miniShell: command not found: ", cm);
	//start_redir_fork(cm, sh);
//	printf("AFUERA hijo i = %d PID %d CMD %s n_pipe %d x = %d\n", i, getpid(), cm->name, sh->n_pipe, x);
	if (!check_cmd(sh->cmd_lst->name) && sh->n_pipe > 0 && (i == 0))
	{
//		printf("1ER IF Hijo PID %d CMD Ext %s \n", getpid(), cm->name);
		dup_stdout(sh, x);
	}
	else if (sh->n_pipe)
	{
		if ((i + 1) == sh->n_forks)
		{
//			printf("2DO IF Hijo PID %d CMD Ext %s \n", getpid(), cm->name);
			if (sh->n_forks > 3 && (sh->n_forks % 2 == 0))
			{
				//printf("HAY 4 COMMANDOS i = %d\n", i);
				dup_stdin_un(sh, x);
			}
			else
				dup_stdin(sh, x);
		}
		else
		{
//			printf("HAY 3 COMMANDOS i = %d\n", i);
			dup_stdin(sh, x);

			dup_stdout_un(sh, x);
		}
	}
	execve(path, cm->argvec, NULL);
}
