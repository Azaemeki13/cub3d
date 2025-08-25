/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:14:23 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/25 11:39:40 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_cell(t_game *g, int i, int x, int y)
{
	t_door	*d;
	char	c;

	d = &g->doors[i];
	d->frac = 0.0;
	d->target = 0;
	d->active = 0;
	c = g->map->map[y][x];
	if (c == 'D')
		d->active = 1;
	else if (c == 'd')
	{
		d->active = 1;
		d->frac = 1.0;
		d->target = 1;
		g->map->map[y][x] = 'D';
	}
}

void	doors_init(t_game *game)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	game->doors = malloc(sizeof(t_door) * (game->map->map_height)
			* (game->map->map_width));
	y = 0;
	while (y < game->map->map_height)
	{
		x = 0;
		while (x < game->map->map_width)
			init_cell(game, i++, x++, y);
		y++;
	}
	game->door_speed = 1.8;
}

t_door	*door_at(t_game *game, int x, int y)
{
	int	w;
	int	h;

	w = game->map->map_width;
	h = game->map->map_height;
	if (x < 0 || y < 0 || x >= w || y >= h)
		return (NULL);
	return (&game->doors[y * w + x]);
}

bool	has_valid_walls(char **map, int x, int y)
{
	bool	horizontal_walls;
	bool	vertical_walls;

	horizontal_walls = (map[y][x - 1] == '1' && map[y][x + 1] == '1');
	vertical_walls = (map[y - 1][x] == '1' && map[y + 1][x] == '1');
	return ((horizontal_walls && !vertical_walls) || (!horizontal_walls
			&& vertical_walls));
}
