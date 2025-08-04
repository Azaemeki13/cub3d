/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:32:23 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/30 13:03:29 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_s(char *s)
{
	int	count_char;

	count_char = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (*s)
	{
		count_char = count_char + write(1, s, 1);
		s++;
	}
	return (count_char);
}
