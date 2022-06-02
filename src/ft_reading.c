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

//Creates a token according to no specific rule
void	ft_next_token(t_sh *sh, int i, char *temp)
{
	int			len;
	t_tokens	*token;
	
	len  = i - sh->start;
	token = ft_create_token(sh);
	token->str = temp;
	//token->str = ft_substr(sh->line, sh->start, len);
	printf("TOKEN created: %p string: %s\n", token, token->str);
	sh->n_tokens++;
	sh->start = -1;
}

//Joins a new character to the string that will become the token
char	*ft_prep_string(t_sh *sh, char *temp, int *i)
{
	char	this_char[2];
	char	*new_temp;

	//printf("TEMP: %s\n", temp);
	this_char[0] = sh->line[*i];
	this_char[1] = '\0';
	if (!temp)
		new_temp = ft_strdup(this_char);
	else
		new_temp = ft_strjoin(temp, this_char);
	//printf("new_tEMP: %s\n", new_temp);
	free(temp);
	return (new_temp);
}

//Choose case that creates a new Token: 1. End of word finishing by whitespace 
//2.SingleQuotes 3.DoubleQuotes 4. End of line
void	ft_parsing(t_sh *sh, int *i)
{
	static char *temp = NULL;

	if (sh->line[*i] < 33 && sh->start >= 0 )
	{
		ft_next_token(sh, *i, temp);
		temp = NULL;
	}
	else if (sh->line[*i] == 39 && ft_quote_real(sh, *i, 0)) 
		temp = ft_single_quoting(sh, i, temp);
	else if (sh->line[*i] == 34 && ft_quote_real(sh, *i, 1))
		temp = ft_double_quoting(sh, i, temp);
	else if (sh->line[*i] > 32 && sh->line[*i] < 127)
		temp = ft_prep_string(sh, temp, i);
	if (sh->line[*i + 1] == '\0' && sh->line[*i] > 32 &&
		   	sh->line[*i] < 127)
	{
		ft_next_token(sh, *i + 1, temp);
		temp = NULL;
	}
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
	printf("number of words: %d\n", sh->n_tokens);
	return ; 
}
