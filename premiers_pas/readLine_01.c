#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_sh
{
	char	*line;
}	t_sh;


void handle_signals(int sing)
{
	//printf("\n"); // Move to a new line
    ioctl(STDIN_FILENO, TIOCSTI, "\n");
    rl_on_new_line(); // Regenerate the prompt on a newline
	//rl_replace_line("", 0); // Clear the previous text
    //rl_redisplay();	
}		

void ft_readline(t_sh *sh)
{
	sh->line = readline("Myshell$ ");
	if (sh->line != 0)
		add_history(sh->line);
}

void init_shell()
{
    printf("\n******************"
        "************************");
    printf("\n\n\t****MINISHELL 42 PROYECT****");
    printf("\n\t\t - ENJOY IT -");
    printf("\n\n*******************"
        "***********************");
    printf("\n\nWelcome @%s \n", getenv("USER"));
    printf("\n");
    //printf("\e[1;1H\e[2J");
//    printf("\e[H\e[2J\e[3J");
    sleep(1);
}

int main(void)
{
	t_sh *sh;

	sh = malloc(sizeof(t_sh));
	char getpwd[100];

	signal(SIGINT, handle_signals);
	init_shell();

	while (1)
	{
		ft_readline(sh);
		if (!strncmp(sh->line, "pwd", 3))
		{
			getcwd(getpwd, sizeof(getpwd));
			printf("%s\n", getpwd);
		}
		if (!sh->line || !strncmp(sh->line, "exit", 4) || (sh->line[0] == 4))
		{
			free(sh->line);
			exit(0);
		}
	free(sh->line);
	}
	return (0);
}	
