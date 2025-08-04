/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:15:10 by chsauvag          #+#    #+#             */
/*   Updated: 2024/11/14 13:24:14 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_stash(void *ptr)
{
	free(ptr);
	return (NULL);
}

char	*read_stash(int fd, char *buffer, char *stash)
{
	char	*temp;
	int		b_read;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
			return (free_stash(stash));
		if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		free(temp);
		if (!stash)
			return (NULL);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

size_t	find_newline(char *stash)
{
	size_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	return (i);
}

char	*extract_line(char **stash)
{
	char	*line;
	char	*new_stash;
	size_t	start;

	if (!*stash || **stash == '\0')
		return (NULL);
	start = find_newline(*stash);
	if ((*stash)[start] == '\n')
		start++;
	line = ft_substr(*stash, 0, start);
	if (!line)
		return (NULL);
	if ((*stash)[start] == '\0')
	{
		free(*stash);
		*stash = NULL;
	}
	else
	{
		new_stash = ft_strdup(*stash + start);
		free(*stash);
		*stash = new_stash;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stash = read_stash(fd, buffer, stash);
	free(buffer);
	if (!stash)
		return (NULL);
	line = extract_line(&stash);
	return (line);
}
