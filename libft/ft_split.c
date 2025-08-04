/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:11:56 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/28 10:49:55 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(const char *s, char c)
{
	size_t	count;
	int		isword;

	isword = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && isword == 0)
		{
			isword = 1;
			count++;
		}
		else if (*s == c)
		{
			isword = 0;
		}
		s++;
	}
	return (count);
}

static char	*malloc_all(const char *s, char c)
{
	const char	*start;
	char		*m_word;
	size_t		len;
	size_t		i;

	len = 0;
	i = 0;
	start = s;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	m_word = (char *)malloc((len + 1) * sizeof(char));
	if (!m_word)
		return (NULL);
	while (i < len)
	{
		m_word[i] = start[i];
		i++;
	}
	m_word[len] = '\0';
	return (m_word);
}

static void	free_all(char **words, size_t num_words)
{
	size_t	i;

	i = 0;
	while (i < num_words)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

char	**ft_fill_words(char **words, const char *s, char c, size_t num_words)
{
	size_t	i;

	i = 0;
	while (*s && i < num_words)
	{
		if (*s != c)
		{
			words[i] = malloc_all(s, c);
			if (!words[i])
			{
				free_all(words, i);
				return (NULL);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (words);
}

char	**ft_split(const char *s, char c)
{
	char	**words;
	size_t	num_words;

	if (!s)
		return (NULL);
	num_words = ft_wordcount(s, c);
	words = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	if (ft_fill_words(words, s, c, num_words) == NULL)
	{
		free_all(words, num_words);
		return (NULL);
	}
	words[num_words] = NULL;
	return (words);
}
