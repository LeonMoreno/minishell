/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:15:28 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/28 18:48:19 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Prints info on all commands
void	ft_print_cmds(t_sh *sh)
{
	t_cmd	*begin;
	int		i;
	int		j;

	i = 1;
	begin = sh->cmd_lst;
	while (begin)
	{
		j = 0;
		while (begin->argvec[j])
			j++;
		j = 0;
		while (begin->token_tab[j])
		{
			printf("Token this: %s\n", begin->token_tab[j]->str);
			j++;
		}
		printf("CMD %d: [ %s ]  has %d args and finishes with %d\n",
			i, begin->name, j - 1, begin->oper);
		i++;
		begin = begin->next;
	}
}

void	free_cmd_lst(t_sh *sh)
{
	t_cmd	*begin;
	t_cmd	*temp;

	begin = NULL;
	if (sh->cmd_lst)
		begin = sh->cmd_lst;
	while (begin)
	{
		temp = begin;
		if (begin->token_tab)
			free(begin->token_tab);
		if (begin->fd_in > 2)
			close(begin->fd_in);
		if (begin->argvec)
			free_doble_arr(begin->argvec);
		if (begin->fdin_str)
			unlink(begin->fdin_str);
		if (begin->fdin_str)
			free(begin->fdin_str);
		begin = begin->next;
		free(temp);
	}
}

void	free_lst(t_sh *sh)
{
	t_tokens	*begin;
	t_tokens	*temp;
	int			i;

	i = 0;
	free(sh->line);
	free(sh->promt);
	begin = sh->token_lst;
	while (begin)
	{
		temp = begin;
		if (begin->str)
			free(begin->str);
		if (begin->argve)
		{
			while (begin->argve[i])
				free(begin->argve[i++]);
			free(begin->argve);
		}
		begin = begin->next;
		free (temp);
	}
	free_cmd_lst(sh);
}

void	free_doble_arr(char **s)
{
	int	i;

	i = 0;
	while (s[i] && s)
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	if (s)
		free(s);
}

/**
 * @brief MSG Err to STD ERR -- TEMPO
 *
 * @cm->name name cmd
 */
void	msg_stderr(char *str, t_cmd *cm, t_sh *sh)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(cm->name, 2);
	ft_putchar_fd('\n', 2);
	if (sh->n_pipe)
		free(sh->pipe);
	free(sh->id_f);
	ft_exit(sh, NULL);
}
