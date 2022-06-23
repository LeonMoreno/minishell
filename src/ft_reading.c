/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:02:24 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/23 12:23:30 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Create a token and puts it at the end of the list
t_tokens	*ft_create_token(t_sh *sh)
{
	t_tokens	*token;
	t_tokens	*begin;

	token = malloc(sizeof(t_tokens));
	token->type = ARG;
	token->next = NULL;
	token->argve = NULL;
	token->str = NULL;
	if (!sh->token_lst)
		sh->token_lst = token;
	else
	{
		begin = sh->token_lst;
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
//1. Its String : token->str  2.Its Type  a:arg b:oper c.pipe 
void	ft_next_token(t_sh *sh, int i, char **temp)
{
	t_tokens	*token;

	if (!*temp)
	{
		sh->start = -1;
		return ;
	}
	token = ft_create_token(sh);
	token->str = *temp;
	sh->n_tokens++;
	if (ft_parsing_meta(sh, i) || ft_parsing_meta(sh, i - 1))
		token->type = OPER;
	if (ft_parsing_meta(sh, i) == 124 && !ft_double_meta(sh, i - 1))
		token->type = PIPE;
	sh->start = -1;
	*temp = NULL;
}

//Joins a new character to the string that will become the token
char	*ft_prep_string(t_sh *sh, char **temp, int *i)
{
	char	this_char[2];
	char	*new_temp;

	this_char[0] = sh->line[*i];
	this_char[1] = '\0';
	if (!*temp)
		new_temp = ft_strdup(this_char);
	else
		new_temp = ft_strjoin(*temp, this_char);
	if (*temp)
	{
		free(*temp);
		*temp = NULL;
	}
	return (new_temp);
}

//FT_PARSING :- Increments string temp and creates new token with it.
// - Checks for quoting rules. " = 34 '= 39
//Cases for next_token: 1. End of word 2. Presence of an operator.
// 3. end of line. 

void	ft_parsing(t_sh *sh, int *i)
{
	static char	*temp = NULL;

	if (sh->line[*i] < 33 && sh->start >= 0)
		ft_next_token(sh, *i, &temp);
	else if (sh->line[*i] == 39 && ft_quote_real(sh, *i, 0))
		temp = ft_single_quoting(sh, i, temp);
	else if (sh->line[*i] == 34 && ft_quote_real(sh, *i, 1))
		temp = ft_double_quoting(sh, i, temp);
	else if (sh->line[*i] == '$' && sh->line[*i + 1] > 32)
		temp = ft_expansion(sh, i, temp);
	else if (sh->line[*i] > 32 && sh->line[*i] < 127)
		temp = ft_prep_string(sh, &temp, i);
	if ((sh->start >= 0 && ft_parsing_meta(sh, (*i) + 1))
		|| ft_parsing_meta(sh, *i))
	{
		if (ft_double_meta(sh, *i))
		{
			*i = *i + 1;
			temp = ft_prep_string(sh, &temp, i);
		}
		ft_next_token(sh, *i, &temp);
	}
	else if (sh->line[*i + 1] == '\0' && sh->line[*i] > 32
		&& sh->line[*i] < 127)
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
	sh->cmd_lst = NULL;
	if (sh->token_lst && ft_parse_err(sh->token_lst))
		ft_init_cmd_lst(sh);
	return ;
}
