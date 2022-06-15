#include "minishell.h"

void	ft_open_file(t_cmd *cmd, int files, char *name, char *content)
{
	int			fd;
	char		*filename;
	char		*path;

	if (cmd->fdin_str)
	{
		printf("Path to unlink: %s\n", cmd->fdin_str);
		unlink(cmd->fdin_str);
		free(cmd->fdin_str);
	}		
	if (cmd->fd_in)
		close(cmd->fd_in);
	if (name)
		fd = open(name, O_RDONLY, 777);
	else
	{
		filename = ft_strjoin(".heredoc", ft_itoa(files));
		fd = open(filename, O_WRONLY | O_CREAT, 0744);
		write(fd, content, ft_strlen(content)); 
		path = ft_strjoin("/", filename);
		cmd->fdin_str = ft_strjoin(getcwd(NULL, 0), path);
		free(filename);
		free(path);
		printf("make new FIle: %s\n", cmd->fdin_str);
	}
	cmd->fd_in = fd;
	printf("FIle '%d'  OPEN \n", cmd->fd_in);
}

char	*ft_heredoc(char *operand)
{
	char	*new_str;
	char	*temp;
	char	*end;

	rl_on_new_line();
	temp = malloc(sizeof(char));
	temp[0] = '\0';
	end = temp;
	while (1)
	{
		new_str = readline("heredoc>");
		if (!ft_strncmp(new_str, operand, ft_strlen(operand) + 1))
			break ;
		end = ft_strjoin(temp, new_str);
		free(temp);
		free(new_str);
		temp = end;	
	}
	free(new_str);
	printf("HEREDOC string: %s\n", end);
	return (end);
}

void	ft_check_redir_input(t_sh *sh)
{
	t_cmd	*begin;
	int		i;
	int		files;
	char	*str;

	files = 0;
	begin = sh->cmd_lst;
	while (begin)
	{
		i = 0;
		while (begin->token_tab[i])
		{
			str = begin->token_tab[i]->str;
			if (begin->token_tab[i]->type == OPER && str[0] == '<'
					&& str[1] == '<')
				ft_open_file(begin, files++, NULL, ft_heredoc(begin->token_tab[i + 1]->str));
			else if (begin->token_tab[i]->type == OPER && str[0] == '<')
				ft_open_file(begin, files++, begin->token_tab[i + 1]->str, NULL);
			i++;
		}
		begin = begin->next;
	}
	return ;
}
