/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:14:23 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 12:51:10 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void doors_init(t_game *game)
{
    int i;
    int x;
    int y;
    
    i = 0;
    game->doors = malloc(sizeof(t_door) * (game->map->map_height) * (game->map->map_width));
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

t_door *door_at(t_game *game, int x, int y)
{
    int w;
    int h;
    
    w = game->map->map_width;
    h = game->map->map_height;
    if (x < 0 || y < 0 || x >= w || y >=h)
        return (NULL);
    return(&game->doors[y * w + x]);
}

static bool is_door_valid(char **map, int x, int y, int map_width, int map_height)
{
    if (x <= 0 || x >= map_width - 1 || y <= 0 || y >= map_height - 1)
        return false;
    bool horizontal_walls = (map[y][x - 1] == '1' && map[y][x + 1] == '1');
    bool vertical_walls = (map[y - 1][x] == '1' && map[y + 1][x] == '1');
    return (horizontal_walls && !vertical_walls) || (!horizontal_walls && vertical_walls);
}

void validate_doors(t_game **game)
{
    char **map = (*game)->map->map;
    int x, y;
    
    y = 0;
    while (y < (*game)->map->map_height)
    {
        x = 0;
        while (x < (*game)->map->map_width)
        {
            if (map[y][x] == 'D' || map[y][x] == 'd')
            {
                if (!is_door_valid(map, x, y, (*game)->map->map_width, (*game)->map->map_height))
                {
                    error_msg("Door not properly placed between walls.");
                    free_game_complete(game);
                    exit(EXIT_FAILURE);
                }
            }
            x++;
        }
        y++;
    }
}
