/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oerrachi <oerrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 16:16:21 by oerrachi          #+#    #+#             */
/*   Updated: 2026/11/06 21:43:13 by oerrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		count;

	count = 0;
	va_start(arg, format);
	while (*format)
	{
		if (*format == '%')
			count += print_format(*(++format), arg);
		else
		{
			write (1, format, 1);
			count++;
		}
		format++;
	}
	va_end(arg);
	return (count);
}
