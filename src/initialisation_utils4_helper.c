/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils4_helper.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:04:17 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 16:45:03 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	len_upto_nl(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

static void	find_size(char **map, int *w, int *h)
{
	int	j;
	int	max;
	int	len;

	j = 0;
	max = 0;
	while (map[j])
	{
		if (ft_isblank(map[j]))
			break ;
		len = len_upto_nl(map[j]);
		if (len > max)
			max = len;
		j++;
	}
	*h = j;
	*w = max;
}

static char	*pad_line(const char *src, int width)
{
	int		len;
	int		x;
	char	*dst;

	len = len_upto_nl(src);
	dst = (char *)ft_calloc(width + 1, sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, src, len + 1);
	x = len;
	while (x < width)
	{
		dst[x] = ' ';
		x++;
	}
	dst[width] = '\0';
	return (dst);
}

static int	pad_all(char **map, int height, int width)
{
	int		y;
	int		len;
	char	*newl;

	y = 0;
	while (y < height)
	{
		len = len_upto_nl(map[y]);
		if (len < width)
		{
			newl = pad_line(map[y], width);
			if (!newl)
				return (0);
			free(map[y]);
			map[y] = newl;
		}
		y++;
	}
	return (1);
}

void	calculate_map_size(t_game **game)
{
	int		w;
	int		h;
	char	**map;

	map = (*game)->map->map;
	find_size(map, &w, &h);
	(*game)->map->map_width = w;
	(*game)->map->map_height = h;
	pad_all(map, h, w);
}
