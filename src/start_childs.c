#include "minishell.h"

/**
 * @brief get variable PATH the env  -- split -- 
 * cherche than chaque line path+name_cmd
 *
 * @param cm struct with the info the cmd
 * @return char* path if le cmd is trouve if not NULL
 */
char	*cmd_path(t_cmd *cm)
{
	char	**path_split;
	char	*path;
	char	*cmd;
	int		i;

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
	free_doble_arr(path_split);
	free(cmd);
	return (NULL);
}

/**
 * @brief execution commands builtins than fork
 *
 * @param cm struct info cmd
 * @param x index pour le pipex
 */
void	start_child_builtins(t_cmd *cm, t_sh *sh, int x)
{
	dup_stdout(sh, x);
	start_builtins(cm, sh);
	exit (0);
}

/**
 * @brief: execution the commands extern than fork 
 * 1) check path if cmd exist. 2) execute selon ordre
 *
 * @param cm: struct with command and argus
 * @param i: index of interactions the forks -- 
 * 1er_cmd i == 0, last_cmd i + 1 == n_forks(number of forks)
 * @param x: index pour le pipex
 */
void	start_child_cmdext(t_cmd *cm, t_sh *sh, int i, int x)
{
	char	*path;

	path = cmd_path(cm);
	if (!path)
		msg_stderr("miniShell: command not found: ", cm);
	if (!check_cmd(sh->cmd_lst->name) && sh->n_pipe > 0 && (i == 0))
		dup_stdout(sh, x);
	else if (sh->n_pipe)
	{
		if ((i + 1) == sh->n_forks)
		{
			//if (sh->n_forks > 3 && (i % 2 == 0))
			if (sh->n_forks > 3)
			{
				//printf("if_else AQUI i = %d\n", i);
				dup_stdin_un(sh, x);
			}
			else
			{
				dup_stdin(sh, x);
			}
		}
		else
		{
			if (sh->n_forks > 3 && (i % 2 == 1) && i != 1)
			{
				printf("else AQUI i = %d\n", i);
				dup_stdin_un(sh, x);
				dup_stdout_dos(sh, x);
			}
			else
			{
//				printf("else AQUI i = %d\n", i);
				dup_stdin(sh, x);
				dup_stdout_un(sh, x);
			}
		}
	}	
	//if (cm->n_redir > 0 && (sh->n_forks == 1 || ((i + 1) == sh->n_forks)))
//	if (cm->n_redir > 0)
//		start_redir_fork(cm, sh);
	execve(path, cm->argvec, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}
