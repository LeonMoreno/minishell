#include "minishell.h"

/**
 * @brief check if cmd is builtins cmd
 *
 * @param s
 * @return 1 if cmd is builtins
 */
int	check_cmd(char *s)
{
	if (!ft_strncmp(s, "exit", 5))
		return (1);
	if (!ft_strncmp(s, "pwd", 4))
		return (1);
	if (!ft_strncmp(s, "cd", 3))
		return (1);
	if (!ft_strncmp(s, "export", 7))
		return (1);
	if (!ft_strncmp(s, "env", 4))
		return (1);
	if (!ft_strncmp(s, "unset", 5))
		return (1);
	if (!ft_strncmp(s, "echo", 5))
		return (1);
	return (0);
}

/**
 * @brief cherche and execute the builtins
 * cherche with strncmp one space the plus in final
 *
 * @param cm struct info cmd
 */
void start_builtins(t_cmd *cm, t_sh *sh)
{
	char *s;
	char **argv;

	//s = sh->token_lst->str;
	//argv = sh->cmd_lst->argvec;
	s = cm->name;
	argv = cm->argvec;

	if (!ft_strncmp(s, "exit", 5))
		ft_exit(sh->line);
	else if (argv[0] && !ft_strncmp(argv[0], "pwd", 4))
		ft_getpwd();
	else if (argv[0] && !ft_strncmp(argv[0], "echo", 5))
		ft_echo(argv);
	else if (argv[0] && !ft_strncmp(argv[0], "cd", 3))
		ft_cd(argv);
	else if (argv[0] && !ft_strncmp(argv[0], "export", 7))
		ft_export(argv);
	else if (argv[0] && !ft_strncmp(argv[0], "env", 4))
		ft_env();
	else if (argv[0] && !ft_strncmp(argv[0], "unset", 5))
		ft_unset(argv);
}
