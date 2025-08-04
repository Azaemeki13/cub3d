/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:12:54 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/21 18:13:43 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (c + 32);
	}
	return (c);
}

/*int	main()
{
	char str[] = "FIJSOJFKSOP";
	int i = 0;
	
	while (str[i])
	{
		printf("%c", ft_tolower(str[i]));
		i++;
	}
	return (0);
}*/
