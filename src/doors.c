/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:14:23 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/19 17:28:52 by cauffret         ###   ########.fr       */
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

 void doors_update(t_game *game, double dt)
 {
    int i;
    int n;
    double step;
    t_door *door;

    n = game->map->map_width * game->map->map_height;
    if (dt > 0.0)
        step = game->door_speed * dt;
    else
        step = 0.03;
    i = 0;
    while(i < n)
    {
        door = &game->doors[i++];
        if (!door->active)
            continue;
        if (door->target && door->frac < 1.0)
        {
            door->frac += step;
            if (door->frac > 1.0)
                door->frac = 1.0;
        }
        else if (!door->target && door->frac > 0.0)
        {
            door->frac  -= step;
            if (door->frac < 0.0)
                door->frac = 0.0;
        }
    }
 }
 
void door_toggle_at(t_game *game, int x, int y)
{
    t_door *door;
    int px;
    int py;

    door = door_at( game, x, y);
    if (!door)
        return;
    px = (int)game->player->player_pos->x;
    py = (int)game->player->player_pos->y;
    if (door->target && door->frac > 0.5)
    {
        if (!(px == x && py == y))
            door->target = 0;

    }
    else
        door->target = 1;
}