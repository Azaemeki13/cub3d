/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:54:16 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/21 17:04:16 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}

/*int	main()
{
	char str[] = "Arrowfdji435af";
	int i = 0;
	
	while (str[i])
	{
		printf("Character '%c' is ASCII: %d\n", str[i], ft_isascii(str[i]));
		i++;
	}
	return (0);
}*/
