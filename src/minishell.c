#include "minishell.h"

void start_shell(t_sh *sh)
{
	while (1)
	{
		sh->line = readline("miniShell$ ");
//		if (sh->line)
//			line_parser(sh);
		check_builtins(sh->line);
		//exec_cmd(sh);
		free(sh->line);
	}
}

int main(void)
{
	t_sh *sh;
// INITIALIZATION D'UN TEST TOKEN
	sh = malloc(sizeof(t_sh));
	sh->tokens = malloc(sizeof(t_tokens *) + 1);
	sh->tokens[0] = malloc(sizeof(t_tokens));
	sh->tokens[0]->type = CMD;
	sh->tokens[0]->str = ft_strdup("ls");
	sh->tokens[0]->argve = malloc(sizeof(char *) * 3);
	sh->tokens[0]->argve[0] = ft_strdup("ls");
	sh->tokens[0]->argve[1] = ft_strdup("-l");
	sh->tokens[0]->argve[2] = NULL;
//fin de l'initialization du TOKEN TEST
//	testt_built(sh); //fonction built-in test
	start_shell(sh); //fonction shell
	return (0);
}

