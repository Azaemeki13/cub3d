/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:19:05 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/21 11:26:16 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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
		printf("Character '%c' is numeric: %d\n", str[i], ft_isdigit(str[i]));
		i++;
	}
	return (0);
}*/
