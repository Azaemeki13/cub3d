/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:15:46 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/21 17:28:01 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - 32);
	}
	return (c);
}

/*int	main()
{
	char str[] = "Arrowfdji435af";
	int i = 0;
	
	while (str[i])
	{
		printf("%c", ft_toupper(str[i]));
		i++;
	}
	return (0);
}*/
