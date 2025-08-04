/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:47:31 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/24 11:20:55 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	total_l;
	size_t	max;
	size_t	i;
	char	*substr;

	if (!s)
		return (NULL);
	total_l = ft_strlen(s);
	if (start >= total_l)
		return (ft_strdup(""));
	max = total_l - start;
	if (len > max)
		len = max;
	substr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
