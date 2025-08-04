/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:27:28 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/21 11:29:46 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c);

int	ft_isdigit(int c);

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
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
		printf("Character '%c' is alnum: %d\n", str[i], ft_isalnum(str[i]));
		i++;
	}
	return (0);
}*/
