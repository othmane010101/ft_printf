/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oerrachi <oerrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 16:16:21 by oerrachi          #+#    #+#             */
/*   Updated: 2026/11/02 21:37:43 by oerrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int ft_printf(const char *format, ...)
{
    va_list arg;
    int count;
    
    count = 0;
    va_start(arg, format);
    while (*format)
    {
        if (*format == '%')
            count += print_format(*(++format), arg);
        else
            write (1, format, 1);
        format++;
    }
    va_end(arg);
}

int main()
{
char *c = "othmane";
ft_printf("%s\"", c);
return (0);
    
}