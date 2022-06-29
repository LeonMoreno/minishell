/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:18:57 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/29 11:22:47 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_h(t_cmd *cmd, int files, char *content)
{
	char	*filename;
	char	*path;
	int		fd;

	if (cmd->fdin_str)
	{
		unlink(cmd->fdin_str);
		free(cmd->fdin_str);
		cmd->fdin_str = NULL;
	}
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	path = ft_itoa(files);
	filename = ft_strjoin(".heredoc", path);
	free(path);
	fd = open(filename, O_RDWR | O_CREAT, 0000777);
	write(fd, content, ft_strlen(content));
	free(content);
	path = ft_strjoin("/", filename);
	free(filename);
	filename = getcwd(NULL, 0);
	cmd->fdin_str = ft_strjoin(filename, path);
	free(path);
	free(filename);
	cmd->fd_in = fd;
}

void	ft_open_file(t_cmd *cmd, char *name)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fdin_str)
	{
		unlink(cmd->fdin_str);
		free(cmd->fdin_str);
		cmd->fdin_str = NULL;
	}
	cmd->fd_in = open(name, O_RDONLY, 0000777);
	if (cmd->fd_in == -1)
		perror(name);
}

char	*ft_heredoc(char *operand, t_sh *sh)
{
	char	*new_str;
	char	*temp;
	char	*end;

	rl_on_new_line();
	temp = malloc(sizeof(char));
	temp[0] = '\0';
	ft_sig_cancel();
	while (1)
	{
		new_str = readline("heredoc>");
		if (new_str == NULL)
			ft_exit_here(temp, sh);
		if (!ft_strncmp(new_str, operand, ft_strlen(operand) + 1))
			break ;
		end = ft_strjoin(temp, new_str);
		free(temp);
		free(new_str);
		temp = ft_strjoin(end, "\n");
		free(end);
	}
	temp = ft_expand_here(sh, temp);
	free(new_str);
	return (temp);
}

char	*ft_fork_here(char *operand, t_sh *sh)
{
	int		i_pipe[2];
	int		me;
	char	*temp;
	char	buf[10240];

	me = 0;
	while (me < 10240)
		buf[me++] = '\0';
	pipe(i_pipe);
	me = fork();
	if (me == 0)
		child_here(i_pipe, sh, operand);
	close(i_pipe[1]);
	ft_silence();
	read(i_pipe[0], buf, 10240);
	close(i_pipe[0]);
	temp = ft_strdup(buf);
	ft_sigaction();
	return (temp);
}

void	ft_check_redir_input(t_sh *sh)
{
	t_cmd		*begin;
	int			i;
	int			files;
	t_tokens	**tab;

	files = 0;
	begin = sh->cmd_lst;
	while (begin)
	{
		i = 0;
		while (begin->token_tab[i])
		{
			if (begin->fd_in == -1)
				break ;
			tab = begin->token_tab;
			if (tab[i]->type == OPER && tab[i]->str[0] == '<'
				&& tab[i]->str[1] == '<')
				ft_open_h(begin, files++, ft_fork_here(tab[i + 1]->str, sh));
			else if (tab[i]->type == OPER && tab[i]->str[0] == '<')
				ft_open_file(begin, tab[i + 1]->str);
			i++;
		}
		begin = begin->next;
	}
	return ;
}
