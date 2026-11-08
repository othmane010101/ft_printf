/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oerrachi <oerrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 22:09:30 by oerrachi          #+#    #+#             */
/*   Updated: 2026/11/07 16:25:32 by oerrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hexa(unsigned int nb, char c)
{
	char	*base;
	
	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_putnbr_hexa(nb / 16, c);
	}
		write (1, &base[nb % 16], 1);
}
