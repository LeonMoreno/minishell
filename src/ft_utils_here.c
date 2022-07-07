/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:30:35 by agrenon           #+#    #+#             */
/*   Updated: 2022/07/07 15:39:55 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	child_here(int *i_pipe, t_sh *sh, char *operand)
{
	char	*temp;

	close(i_pipe[0]);
	temp = ft_heredoc(operand, sh);
	write(i_pipe[1], temp, ft_strlen(temp));
	free(temp);
	close(i_pipe[1]);
	ft_exit(sh, NULL);
}
