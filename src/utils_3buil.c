/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3buil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 19:33:10 by lmoreno           #+#    #+#             */
/*   Updated: 2022/06/29 20:11:14 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getpwd(t_sh *sh)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		perror("pwd ");
	else
	{
		ft_printf("%s\n", buf);
		free(buf);
	}
	sh->last_re = 0;
}
