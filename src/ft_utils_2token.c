#include "minishell.h"

int		ft_messa_pare(t_tokens *begin, int *left, int *right)
{
	int	a;

	a = 0;
	if (begin->type == PARE && begin->str[0] == '(')
		*left = *left + 1;
	else if (begin->type == PARE && begin->str[0] == ')')
		*right = *right + 1;
	if (*right > *left)
		a = write(2, "syntax error: parenthesis can't be closed-> ", 45);
	else if (begin->type == PARE && begin->str[0] == '('
		&& (!begin->cm_line || !begin->cm_line[0]))
		a = write(2, "parse error: parenthesis is misuse-> ", 36);
	else if (begin->type == PARE && begin->str[0] == ')' && begin->next
		&& (begin->next->type == ARG || begin->next->type == PARE))
		a = write(2, "parse error: parenthesis needs operator-> ", 40);	
	if (a)
	{
		write(2, begin->str, 1);
		if (a == 36 && begin->next)
			write(2, begin->next->str, ft_strlen(begin->next->str));
		write(2, "\n", 1);
	}
	return (a);
}

void	ft_argvec_pare(t_cmd *cm_pare, t_tokens *n)
{
	cm_pare->name = cm_pare->token_tab[0]->str;
	if (cm_pare->name[0] == '(')
	{
		cm_pare->argvec = malloc(sizeof(char *) * 3);
		cm_pare->argvec[0] = ft_strdup("./minishell");
		cm_pare->argvec[1] = ft_strdup(cm_pare->token_tab[0]->cm_line);
		cm_pare->argvec[2] = NULL;
	}
	else
	{
		cm_pare->argvec = malloc(sizeof(char *) *2);
		cm_pare->argvec[0] = ft_strdup(cm_pare->name);
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
		if (len > 0)
			pare->cm_line = ft_substr(sh->line, *i + 1, len);
		*i = *i + len;
	}
	return ;
}
