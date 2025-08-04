/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:19:00 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/23 10:53:40 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] && big[i + j] && (i + j) < len)
		{
			if (big[i + j] != little[j])
				break ;
			j++;
		}
		if (!(little[j]))
		{
			return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

/*int	main() 
{
	char haystack[] = "Arrow in the knee";
	char needle[] = "the";
	size_t len = 15;
	char *result = ft_strnstr(haystack, needle, len);
	if (result)
	{
		printf("Found substring: %s\n", result);
	}
	else
	{
		printf("Substring not found.\n");
	}
	return 0;
}*/
