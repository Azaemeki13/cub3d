/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:04:51 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/30 11:11:24 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_process_format(char specifier, va_list ap)
{
	if (specifier == 'c')
		return (ft_printf_c(va_arg(ap, int)));
	else if (specifier == 's')
		return (ft_printf_s(va_arg(ap, char *)));
	else if (specifier == 'p')
		return (ft_printf_p(va_arg(ap, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_printf_d(va_arg(ap, int)));
	else if (specifier == 'x')
		return (ft_printf_x(va_arg(ap, unsigned int), 0));
	else if (specifier == 'X')
		return (ft_printf_x(va_arg(ap, unsigned int), 1));
	else if (specifier == 'u')
		return (ft_printf_u(va_arg(ap, unsigned int)));
	else if (specifier == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	size_t		i;
	int			count;

	count = 0;
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += ft_process_format(format[++i], ap);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
