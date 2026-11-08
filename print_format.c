/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oerrachi <oerrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 21:43:48 by oerrachi          #+#    #+#             */
/*   Updated: 2026/11/07 09:53:36 by oerrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int	print_format(char c, va_list arg)
{
	if (c == 'c')
		return (ft_put_char(va_arg(arg, int)));
	else if (c == 's')
		return (ft_put_str(va_arg(arg, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_intlen(va_arg(arg, int)));
	else if (c == 'u')
		return (ft_uintlen(va_arg(arg, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_hexalen(va_arg(arg, unsigned int), c));
	else if (c == 'p')
		return (ft_putpthexa(va_arg(arg, void *)));
	else if (c == '%')
		return (write (1, "%", 1));
	return (0);
}
