/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:36:01 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/30 17:03:40 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex(unsigned int n, char *base)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += ft_puthex(n / 16, base);
	}
	count += write(1, &base[n % 16], 1);
	return (count);
}

int	ft_printf_x(unsigned int n, int up)
{
	char	*base;
	int		count;

	if (up == 1)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n == 0)
	{
		return (write(1, "0", 1));
	}
	count = ft_puthex(n, base);
	return (count);
}
