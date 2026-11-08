/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oerrachi <oerrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 09:38:09 by oerrachi          #+#    #+#             */
/*   Updated: 2026/11/07 09:48:40 by oerrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr(unsigned int n)
{
	char	c;

	if (n >= 10)
	{
		ft_putnbr(n / 10);
	}
	c = n % 10 + '0';
	write (1, &c, 1);
}

int	ft_uintlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	ft_putnbr(n);
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}
