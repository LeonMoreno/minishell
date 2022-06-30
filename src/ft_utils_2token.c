#include "minishell.h"

void	ft_argvec_pare(t_cmd *cm_pare, t_tokens *n)
{
	cm_pare->name = cm_pare->token_tab[0]->str;
	if (cm_pare->name[0] == '(')
	{
		cm_pare->argvec = malloc(sizeof(char *) * 3);
		cm_pare->argvec[0] = ft_strdup("./minishell");
		cm_pare->argvec[1] = cm_pare->token_tab[0]->cm_line;
		cm_pare->argvec[2] = NULL;
	}
	else
	{
		cm_pare->argvec = malloc(sizeof(char *) *2);
		cm_pare->argvec[0] = cm_pare->name;
		cm_pare->argvec[1] = NULL;
	}	
	if (n && n->type == PIPE && oper_meta(n->str, 0) == 38)
		cm_pare->oper = AND;
	if (n && n->type == PIPE && oper_meta(n->str, 0) == 124)
		cm_pare->oper = OR;
}

int		ft_len_pare(t_sh *sh, char *str, int index)
{
	int i;
	int	p_count;

	p_count = 0;
	i = index;
	while (str[i])
	{
		if (str[i] == 39)
			i = ft_quote_real(sh, index, 0);	
		if (str[i] == 34)
			i = ft_quote_real(sh, index, 1);
		if (str[i] == '(')
			p_count++;
		if (str[i] == ')' && !p_count)
			return (i);
		else if (str[i] == ')')
			p_count--;
		i++;
	}
	return (-1);
}

void	ft_substract_pare(t_sh *sh, t_tokens *pare, int *i)
{
	int		len;
	
	pare->type = PARE;
	if (pare->str[0] == '(')
	{
		len = ft_len_pare(sh, sh->line, *i + 1) - 1 - *i;
		//printf("Len parenthesis str: %d int i : %d\n", len, *i);
		if (len > 0)
			pare->cm_line = ft_substr(sh->line, *i + 1, len);
		*i = *i + len;
		//printf("Str parenthèse: %s\n", pare->cm_line);
	}
	return ;
}
