#include "myshell.h"

void ft_getpwd(void)
{
	char pwd[100];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}

void ft_exit(char *str)
{
	free(str);
	exit (EXIT_SUCCESS);
}

void ft_echo(char *str)
{
	printf("%s \n", str);
}
