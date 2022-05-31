#ifndef MYSHELL_H
# define MYSHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void ft_getpwd(void);
void ft_exit(char *str);
void ft_echo(char *str);

#endif
