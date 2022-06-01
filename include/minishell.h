#ifndef MINISHELL_H
# define MINISHELL_H

// Include stddef stdio stlib unistd limits stdarg fcntl
#include "../libft/include/libft.h"

// Include readline
#include <readline/readline.h>

// Variable global env
extern char **environ;

enum 
{
	CMD,
	ARG,
	OPER,
};

typedef struct s_tokens
{
	int		type;
	char	*str;
	char	**argve;
	char	*path;
}	t_tokens;

typedef struct s_sh
{
	char	*line;
	char	**line_split;
	char	**envs;
	t_tokens	**tokens;
}	t_sh;

//Functions builtins
void check_builtins(t_sh *sh);
void ft_exit(char *line);
void ft_getpwd(void);
void ft_echo(char **line_split);
void ft_cd(char **line_split);
void ft_export(void);
void ft_env(t_sh *sh);


#endif
