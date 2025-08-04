/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:34:23 by chsauvag          #+#    #+#             */
/*   Updated: 2024/11/05 10:34:29 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_u(unsigned int n)
{
	char	num;
	int		count;

	count = 0;
	if (n >= 10)
	{
		count = count + ft_printf_u(n / 10);
	}
	num = (n % 10) + '0';
	count = count + (write(1, &num, 1));
	return (count);
}
