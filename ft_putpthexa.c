/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpthexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oerrachi <oerrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 22:34:57 by oerrachi          #+#    #+#             */
/*   Updated: 2026/11/07 16:27:33 by oerrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptnbr_hexa(unsigned long long nb)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_putptnbr_hexa(nb / 16);
	}
	write (1, &base[nb % 16], 1);
}

int	ft_putpthexa(void *v)
{
	unsigned long long	nb;
	int					i;

	if (v == NULL)
		return (ft_put_str("(nil)"));
	i = 0;
	nb = (unsigned long long )v;
	write (1, "0x", 2);
	if (nb == 0)
	{
		write (1, "0", 1);
		return (3);
	}
	ft_putptnbr_hexa(nb);
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 16;
		i++;
	}
	return (i + 2);
}
