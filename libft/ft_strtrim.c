/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:44:19 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/25 19:44:27 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

static int	ft_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;
	size_t	len_trimmed;
	char	*s_trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_set(s1[start], set))
		start++;
	while (end > start && ft_set(s1[end - 1], set))
		end--;
	len_trimmed = end - start;
	s_trimmed = (char *)malloc(sizeof(char) * (len_trimmed + 1));
	if (!s_trimmed)
		return (NULL);
	ft_strlcpy(s_trimmed, &s1[start], len_trimmed + 1);
	s_trimmed[len_trimmed] = '\0';
	return (s_trimmed);
}

/*int main()
{
	char const *str = "aaaaaaaaHello Worldaaaaaa";
	char const *set = "a";

	printf("%s", ft_strtrim(str, set));
	return 0;
}*/
