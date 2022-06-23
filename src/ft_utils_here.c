/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:30:35 by agrenon           #+#    #+#             */
/*   Updated: 2022/06/23 11:10:54 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_here(int *i_pipe, t_sh *sh, char *operand)
{
	char	*temp;

	close(i_pipe[0]);
	temp = ft_heredoc(operand, sh);
	write(i_pipe[1], temp, ft_strlen(temp));
	close(i_pipe[1]);
	free_lst(sh);
	exit(0);
}
