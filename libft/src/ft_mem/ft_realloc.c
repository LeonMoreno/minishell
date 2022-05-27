/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:41:54 by lmoreno           #+#    #+#             */
/*   Updated: 2021/12/16 18:41:56 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *src, size_t size)
{
	void	*dst;

	dst = malloc(size);
	if (!dst)
	{
		free(src);
		return (NULL);
	}
	if (!src)
	{
		free(dst);
		return (NULL);
	}
	ft_memmove(dst, src, size);
	free(src);
	src = NULL;
	return (dst);
}
