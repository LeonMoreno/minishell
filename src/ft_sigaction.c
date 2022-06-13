#include "minishell.h"


void	ft_handler(int sig)
{
	//struct termios term;
//	char	*prompt;
//	int		len;

	if (sig == SIGINT) 	
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		//prompt = ft_strjoin(getenv("USER"), "@miniShell$ ");
		//len = ft_strlen(prompt);

		//tcgetattr(0, &term);
		//tcsetattr(0, TCSANOW, &term);
		//write(1, "agrenon@miniShell$ ", 21);
	
	}
	return ;
}

void	ft_sigaction(void)
{
	//struct termios term;
	struct sigaction	action;
	//sigset_t			s;

	signal(SIGQUIT, SIG_IGN);
	//tcgetattr(0, &term);
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	//sigaddset(&action.sa_mask, SIGQUIT);
	action.sa_handler = ft_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	//sigaction(SIGQUIT, &action, NULL);
}
