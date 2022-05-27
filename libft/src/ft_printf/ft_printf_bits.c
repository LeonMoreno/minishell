/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:42:26 by lmoreno           #+#    #+#             */
/*   Updated: 2021/12/16 18:43:22 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_bits(int nb, int *len)
{
	int	bits;

	bits = sizeof(nb) * 8;
	while (bits--)
		ft_putchar((nb >> bits & 1) + 48, len);
}
