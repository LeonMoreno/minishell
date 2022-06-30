/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:27:01 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/30 11:25:47 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Include stddef stdio stlib unistd limits stdarg fcntl
# include "../libft/include/libft.h"

// Include readline
# include <readline/readline.h>
# include <readline/history.h>
# include "colours.h"
//Include pout wait
# include <sys/wait.h>

# include <stdbool.h>
//Include pour sigaction
# include <signal.h>
# include <termios.h>
# include <dirent.h>

// Variable global env
extern char	**environ;

enum
{
	CMD,
	ARG,
	OPER,
	OPERD,
	PIPE,
	PARE,
	AND,
	OR,
	QUOTE,
	OUT = 0,
	IN
};

typedef struct s_pip
{
	int		p[2];
}	t_pip;

typedef struct s_argve
{
	char			*str;
	struct s_argve	*next;
}	t_argve;

typedef struct s_tokens
{
	int				type;
	char			*str;
	char			**argve;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_cmd
{
	t_tokens		**token_tab;
	char			**argvec;
	char			argvec_count;
	char			*name;
	int				n_r_out;
	int				fd_in;
	char			*fdin_str;
	int				*fd_out;
	int				oper;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_sh
{
	char		*line;
	t_cmd		*cmd_lst;
	t_tokens	*token_lst;
	t_pip		*pipe;
	pid_t		*id_f;

	int			last_re;
	int			n_cmd;
	int			n_pipe;
	int			n_forks;
	int			n_tokens;
	int			start;
	int			true_fd_out;
	int			last_oper;
	char		*promt;
	char		**env;
	char		*tmp;
}	t_sh;

//Functions builtins
void		ft_exit(t_sh *sh, char **argv);
void		ft_getpwd(t_sh *sh);
void		ft_echo(char **s, t_sh *sh);
void		ft_cd(char **s, t_sh *sh);
void		ft_export(char *s, t_sh *sh);
void		ft_env(t_sh *sh);
void		ft_unset(char **s, t_sh *sh);
void		start_env(t_sh *sh);
int			ft_len_env(char *key_s, t_sh *sh);
void		ft_cd_home_relativo(char **s, t_sh *sh, char *oldpwd);
int			ft_chr_n(char *s, int *ctr, t_sh *sh);
void		ft_perror(char *s, t_sh *sh);

//Functions parser
void		line_parser(t_sh *sh);
void		ft_parsing(t_sh *sh, int *i);
int			ft_quote_real(t_sh *sh, int i, int a);
char		*ft_expansion(t_sh *sh, int *i, char *temp);
char		*ft_double_quoting(t_sh *sh, int *i, char *temp);
char		*ft_single_quoting(t_sh *sh, int *i, char *temp);
char		*ft_prep_string(t_sh *sh, char **temp, int *i);
int			ft_parsing_meta(t_sh *sh, int i);
int			ft_double_meta(t_sh *sh, int i);
int			oper_meta(char *str, int i);
int			ft_parse_err(t_tokens *list);
t_tokens	*ft_create_token(t_sh *sh);

//Functions Commands
int			ft_size(t_tokens *lsist, int mode);
void		ft_argvec_init(t_tokens *index, t_cmd *this_cmd);
void		ft_argvec_zero(char **argvec, int len);
void		ft_init_cmd_lst(t_sh *sh);

//Functions Wildcards
int			check_wild(char *str);
char		**openthydir(char **argvec, char *wild_str, int len_argve, int *i);
t_argve		*argve_lst(t_argve *lst, char *str);
void		ft_free_argve_lst(t_argve *lst);
int			size_alst(t_argve *lst);
char		**new_argve_tab(char **argvec, t_argve *st, int old, char **tab);
int			ft_is_accepted(char *wild_str, char *str);
int			ft_wild_next(char *wild_str, int j);
int			ft_wild_split_ncmp(char *wild, char *str);

//Functions Heredoc
char		*ft_heredoc(char *operand, t_sh *sh);
void		ft_check_redir_input(t_sh *sh);
void		ft_exit_here(char *temp, t_sh *sh);
void		child_here(int *i_pipe, t_sh *sh, char *operand);
char		*ft_expand_here(t_sh *sh, char *line);

//Functions Sigaction
void		ft_sigaction(void);
void		ft_sig_cancel(void);
void		ft_silence(void);

//Functions utils
void		free_lst(t_sh *sh);
void		ft_print_cmds(t_sh *sh);
void		free_doble_arr(char **s);
void		init_var(t_sh *sh);
int			ft_size_arr(char **tab);

//Functions excec_cmd
void		start_exec(t_sh *sh);
void		start_builtins(t_cmd *cm, t_sh *sh);
int			check_cmd(char *s); //int check_builtins(char *s);
void		end_fork(t_sh *sh);
void		start_pipex(t_sh *sh);
int			init_fork(t_sh *sh, t_cmd *top);

//Functions childs fork and pipes
void		start_child_builtins(t_cmd *cm, t_sh *sh, int i);
void		start_child_cmdext(t_cmd *cm, t_sh *sh, int i);
char		*cmd_path(t_cmd *cm);
void		dup_stdin_un(t_sh *sh, int x);
void		dup_stdin(t_sh *sh, int x);
void		dup_stdout_un(t_sh *sh, int x);
void		dup_stdout_dos(t_sh *sh, int x);
void		dup_stdout(t_sh *sh, int x);
void		msg_stderr(char *str, t_cmd *cm, t_sh *sh);
void		ft_exit_fail(t_sh *sh, char **argv);

//Functions redir
void		start_redir(t_cmd *cm);
void		close_redir_buil(t_sh *sh, t_cmd *cm);
void		start_redir_fork(t_cmd *cm, t_sh *sh);
void		start_redir_pipes(t_cmd *cm, t_sh *sh, int x);
void		chr_redir_out(t_cmd *cm, char c);

#endif
