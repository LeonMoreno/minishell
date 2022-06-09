#ifndef MINISHELL_H
# define MINISHELL_H

// Include stddef stdio stlib unistd limits stdarg fcntl
#include "../libft/include/libft.h"

// Include readline
#include <readline/readline.h>
#include <readline/history.h>

//Include pout wait
#include <sys/wait.h>

#include <stdbool.h>

// Variable global env
extern char **environ;

#define OUT 0 /*index pipe extrem READ */
#define IN 1 /*Index pipe extrem WRITE */


enum
{
	CMD,
	ARG,
	OPER,
	OPERD,
	PIPE,
	EXIT = 0,
	ENV,
	CD,
	EXPRT,
};

typedef struct s_pip
{
	int		p[2];
}	t_pip;

typedef struct s_tokens
{
	int				type;
	char			*str;
	char			**argve;
	char			*path;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_cmd
{
	t_tokens		**token_tab;
	char			**argvec;
	char			*name;
	int				n_redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_sh
{
	char		*line;
	t_cmd		*cmd_lst;
	t_tokens	*token_lst;
	t_pip		*pipe;
	pid_t		*id_f;

	int			n_cmd;
	int			n_pipe;
	//int			m_pipe;
	int			n_forks;
	int			n_tokens;
	int			start;
}	t_sh;

//Functions builtins
void	ft_exit(char *line);
void	ft_getpwd(void);
void	ft_echo(char **line_split);
void	ft_cd(char **line_split);
void	ft_export(char **s);
void	ft_env(void);
void	ft_unset(char **s);

//Functions parser
t_tokens	*ft_create_token(t_sh *sh);
void	line_parser(t_sh *sh);
void	ft_parsing(t_sh *sh, int *i);
int		ft_quote_real(t_sh *sh, int i, int a);
char	*ft_expansion(t_sh *sh, int *i, char *temp);
char	*ft_double_quoting(t_sh *sh, int *i, char *temp);
char	*ft_single_quoting(t_sh *sh, int *i, char *temp);
char	*ft_prep_string(t_sh *sh, char *temp, int *i);
int		ft_parsing_meta(t_sh *sh, int i);
int		ft_double_meta(t_sh *sh, int i);

//Functions Commands
void	ft_argvec_init(t_tokens *index, t_cmd *this_cmd);
void	ft_init_cmd_lst(t_sh *sh);


//Functions utils
void	free_lst(t_sh *sh);
void	ft_print_cmds(t_sh *sh);

//Functions excec_cmd
void	start_exec(t_sh *sh);
void	start_builtins(t_cmd *cm, t_sh *sh);
int		check_cmd(char *s); //int check_builtins(char *s);
void	end_fork(t_sh *sh);

//Functions childs fork
void	start_child_builtins(t_cmd *cm, t_sh *sh);
void	start_child_cmdext(t_cmd *cm, t_sh *sh, int i, int x);

//Functions childs fork
char	*cmd_path(t_cmd *cm);

#endif
