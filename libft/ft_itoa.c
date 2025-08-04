/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:07:40 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/24 17:27:19 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char				*str;
	size_t				len;	
	unsigned int		num;

	len = ft_nlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (len > 0 && num != 0)
	{
		str[--len] = ((num % 10) + '0');
		num = num / 10;
	}
	if (n == 0)
		str[0] = '0';
	return (str);
}

/*int main()
{
    int number = 2147483648;
    char *result = ft_itoa(number);

    printf("The string representation of %d is: %s\n", number, result);

    free(result);  // Free the allocated memory
    return 0;
}*/
