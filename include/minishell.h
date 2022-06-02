#ifndef MINISHELL_H
# define MINISHELL_H

// Include stddef stdio stlib unistd limits stdarg fcntl
#include "../libft/include/libft.h"

// Include readline
#include <readline/readline.h>

#include <stdbool.h>

enum 
{
	CMD,
	ARG,
	OPER,
};

typedef struct s_tokens
{
	int				type;
	char			*str;
	char			**argve;
	char			*path;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_sh
{
	char		*line;
	t_tokens	*token_top;
	
	int			n_tokens;
	int			start;
	int			len;
}	t_sh;

//Functions builtins
void ft_exit(char *str);
void ft_getpwd(void);
void ft_echo(char *str);

//Functions parser
t_tokens	*ft_create_token(t_sh *sh);
void	line_parser(t_sh *sh);
void	ft_parsing(t_sh *sh, int *i);
int		ft_quote_real(t_sh *sh, int i, int a);
char	*ft_double_quoting(t_sh *sh, int *i, char *temp);
char	*ft_single_quoting(t_sh *sh, int *i, char *temp);
char	*ft_prep_string(t_sh *sh, char *temp, int *i);
#endif
