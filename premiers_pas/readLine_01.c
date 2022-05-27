#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void handle_signals(int sing)
{
	if (sing == SIGINT)
	{
		//printf("\n");
		rl_on_new_line();
	}
		
}		

int main(void)
{
	char *str;
	char getpwd[100];

	signal(SIGINT, handle_signals);

	while (1)
	{
		str = readline("Myshell $ ");
		if (str)
			add_history(str);
		if (!strncmp(str, "pwd", 3))
		{
			getcwd(getpwd, sizeof(getpwd));
			printf("%s\n", getpwd);
		}
		if (!str || !strncmp(str, "exit", 4))
		{
			free(str);
			break;
		}
		printf ("%s \n", str);
	free(str);
	}
	return (0);
}	
