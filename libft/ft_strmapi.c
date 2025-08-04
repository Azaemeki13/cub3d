/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:27:33 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/25 10:49:00 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	s_len;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	result = malloc((s_len + 1) * sizeof(char));
	if (!result)
	{
		return (NULL);
	}
	while (i < s_len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
