/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oerrachi <oerrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 19:16:43 by oerrachi          #+#    #+#             */
/*   Updated: 2026/11/06 22:01:18 by oerrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		print_format(char c, va_list arg);
int		ft_put_char(int c);
int		ft_put_str(char *str);
int		ft_intlen(int n);
int		ft_hexalen(unsigned int nb, char c);
int		ft_putpthexa(void *v);
int		ft_uintlen(unsigned int n);
void	ft_putnbr_hexa(unsigned int nb, char c);

#endif
