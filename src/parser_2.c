/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:29:38 by cauffret          #+#    #+#             */
/*   Updated: 2025/09/04 09:44:29 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D'
		|| c == 'd');
}

bool	map_no_exposed_to_void(char **map, int w, int h)
{
	int	x;
	int	y;

	if (!map || w <= 2 || h <= 2)
		return (false);
	y = 1;
	while (y < h - 1)
	{
		x = 1;
		while (x < w - 1)
		{
			if (is_walkable(map[y][x]))
			{
				if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || map[y][x
					- 1] == ' ' || map[y][x + 1] == ' ')
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}
