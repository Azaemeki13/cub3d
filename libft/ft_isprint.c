/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:05:30 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/21 17:06:52 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
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
		printf("Character '%c' is printable: %d\n", str[i], ft_isprint(str[i]));
		i++;
	}
	return (0);
}*/
