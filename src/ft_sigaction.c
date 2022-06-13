#include "minishell.h"


void	ft_handler(int sig)
{
	if (sig == SIGINT) 	
	{
	write(1, "\nminiShell'$' ", 10);
	rl_redisplay();
	rl_on_new_line();
	}	
	else
		(void) sig;
	
	//(void) sig;
	return ;
}

void	ft_sigaction(void)
{

	struct sigaction	action;
	sigset_t			s;

	sigemptyset(&action.sa_mask);
	action.sa_handler = ft_handler;
	action.sa_flags = SA_RESTART;
	sigaddset(&s, SIGINT);
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	sigemptyset(&s);
	sigaddset(&s, SIGQUIT);
	sigprocmask(SIG_BLOCK, &s, NULL);
}
