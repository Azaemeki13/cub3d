/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:02:42 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/31 10:34:12 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_hex(unsigned long n)
{
	char	*hex_digit;
	int		count;

	hex_digit = "0123456789abcdef";
	count = 0;
	if (n >= 16)
	{
		count += ft_putnbr_hex(n / 16);
	}
	count += write(1, &hex_digit[n % 16], 1);
	return (count);
}

int	ft_printf_p(void *ptr)
{
	unsigned long	ad;
	int				count;

	count = 0;
	ad = (unsigned long)ptr;
	if (ad == 0)
	{
		count += write(1, "(nil)", 5);
	}
	else
	{
		count += write(1, "0x", 2);
		count += ft_putnbr_hex(ad);
	}
	return (count);
}
