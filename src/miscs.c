/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:19:25 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/05 12:00:27 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int ft_isspace(char c)
{
    if (!c)
        return (0);
    else if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == 'r')
        return (1);
    return (0);
}

int ft_isblank(char *str)
{
    if (!str)
        return (0);
    int i;

    i = 0;
    while((ft_isspace(str[i])) || str[i] == '\n')
        i++;
    if (i != (ft_strlen(str)))
        return(0);
    else
        return(1);
}

int ft_special_len(char *str, int separator)
{
    int i;
    
    i = 0;
    if (!str)
        return (i);
    while (str[i] && str[i] != separator)
        i++;
    return(i);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;

	i = 0;
	while (s[i] && i < n)
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int count_strings(char **str)
{
    int i;

    if (!str || !*str)
        return (0);
    i = 0;
    while(str[i])
        i++;
    return(i);
}
