#include "minishell.h"

int check_builtins(char *s)
{
	if(!ft_strncmp(s, "exit", 5))
			return (1);
	if(!ft_strncmp(s, "pwd", 4))
			return (1);
	if(!ft_strncmp(s, "cd", 3))
			return (1);
	if(!ft_strncmp(s, "export", 7))
			return (1);
	if(!ft_strncmp(s, "env", 4))
			return (1);
	if(!ft_strncmp(s, "unset", 5))
			return (1);
	if(!ft_strncmp(s, "echo", 5))
			return (1);
	return (0);
}


void start_exec(t_sh *sh)
{
	t_cmd *cm;
	t_tokens *t;
	int pip;

	pip = 0;
	cm = sh->cmd_lst;
	t = sh->token_lst;
	while(cm)
	{
		printf("cmd = %s\n", cm->name);
		cm = cm->next;
	}
	while (t)
	{
		if (t->type == PIPE)
			pip++;
		t = t->next;
	}

	printf("No PIPES = %d\n", sh->n_pipe);
	if (check_builtins(sh->cmd_lst->name))
		start_builtins(sh);
}
