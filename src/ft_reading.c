#include "minishell.h"

//Create a token and puts it at the end of the list
t_tokens	*ft_create_token(t_sh *sh)
{
	t_tokens *token;
	t_tokens *begin;
	
	token =	malloc(sizeof(t_tokens));
	token->next = NULL;
	if (!sh->token_top)
		sh->token_top = token;
	else
	{
		begin = sh->token_top;
		while (begin)
		{
			if (!begin->next)
			{
				begin->next = token;
				break ;
			}
			begin = begin->next;
		}
	}
	return (token);
}

//Initiate a token. Newly created token receives :
//1. Its String : token->str  2.Its Type  1:arg 2:oper 3.pipe
void	ft_next_token(t_sh *sh, int i, char **temp)
{
	int			len;
	t_tokens	*token;
	
	len  = i - sh->start;
	token = ft_create_token(sh);
	token->str = *temp;
	sh->n_tokens++;
	token->type = ARG;
	if (ft_parsing_meta(sh, i))
		token->type = OPER;
	else if (ft_parsing_meta(sh, i) == 124 && ft_double_meta(sh, i))
		token->type = PIPE;	
	sh->start = -1;
	printf("TOKEN Type: %d String: [ %s ]\n", token->type, token->str);
	*temp = NULL;
}

//Joins a new character to the string that will become the token
char	*ft_prep_string(t_sh *sh, char *temp, int *i)
{
	char	this_char[2];
	char	*new_temp;

	this_char[0] = sh->line[*i];
	this_char[1] = '\0';
	if (!temp)
		new_temp = ft_strdup(this_char);
	else
		new_temp = ft_strjoin(temp, this_char);
	free(temp);
	return (new_temp);
}

//FT_PARSING :- Increments string temp and creates new token with it.
// - Checks for quoting rules
//Cases for next_token: 1. End of word 2. Presence of operator.
// 3. end of line. 

void	ft_parsing(t_sh *sh, int *i)
{
	static char *temp = NULL;

	if (sh->line[*i] < 33 && sh->start >= 0 )
		ft_next_token(sh, *i, &temp);
	else if (sh->line[*i] == 39 && ft_quote_real(sh, *i, 0)) 
		temp = ft_single_quoting(sh, i, temp);
	else if (sh->line[*i] == 34 && ft_quote_real(sh, *i, 1))
		temp = ft_double_quoting(sh, i, temp);
	else if (sh->line[*i] > 32 && sh->line[*i] < 127)
		temp = ft_prep_string(sh, temp, i);
	if ( (sh->start >= 0 && ft_parsing_meta(sh, (*i) + 1)) || ft_parsing_meta(sh, *i))
	{
		if (ft_double_meta(sh, *i))
		{
			*i = *i + 1;
			temp = ft_prep_string(sh, temp, i);
		}
		ft_next_token(sh, *i, &temp);
	}
	else if (sh->line[*i + 1] == '\0' && sh->line[*i] > 32 &&
		   	sh->line[*i] < 127)
		ft_next_token(sh, *i + 1, &temp);
}

//Loops and parse the line received and stored in sh->line.
//Initialize the start of a word 
void	line_parser(t_sh *sh)
{
	int		i;
	
	i = 0;
	sh->n_tokens = 0;
	sh->start = -1;
	while (sh->line[i])
	{
		if (sh->line[i] > 32 && sh->line[i] < 127 && sh->start < 0)
			sh->start = i;
		ft_parsing(sh, &i);
		i++;
	}
	return ; 
}
