/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oerrachi <oerrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 21:33:41 by oerrachi          #+#    #+#             */
/*   Updated: 2026/11/06 21:40:01 by oerrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n)
{
	char	c;

	if (n < 0)
	{
		write (1, "-", 1);
		n = -n;
		if (n == -2147483648)
		{
			write (1, "2147483648", 10);
			return ;
		}
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
	}
	c = n % 10 + '0';
	write (1, &c, 1);
}

int	ft_intlen(int n)
{
	int	i;

	i = 0;
	ft_putnbr(n);
	if (n < 0 || n == 0)
	{
		i++;
		n = -n;
	}
	if (n == -2147483648)
		return (11);
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}
