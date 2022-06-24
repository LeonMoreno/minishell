/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigaction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:55:38 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/24 12:47:05 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	ft_handler_here(int sig)
{
	if (sig == SIGINT)
	{
		write(4, "\0", 1);
		close(4);
		exit(0);
	}
}

void	ft_silence(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_sig_cancel(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, ft_handler_here);
}

void	ft_sigaction(void)
{
	struct sigaction	action;

	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	action.sa_handler = ft_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
}
