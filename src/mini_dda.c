/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:33:19 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/19 14:55:49 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

 int interact_cast(t_game *g)
{
    t_ray ray;
    double px;
    double py;
    int map_x;
    int map_y;
    int step_x;
    int step_y;
    double delta_x;
    double delta_y;
    double side_dist_x;
    double side_dist_y;
    int hit;
    int side;
    int tile;
    double t;
    
    px = g->player->player_pos->x;
    py = g->player->player_pos->y;
    map_x = (int)g->player->player_pos->x;
    map_y = (int)g->player->player_pos->y;
    ray.ray_dir.x = g->player->vector_dir->x;
    ray.ray_dir.y = g->player->vector_dir->y;
    if (ray.ray_dir.x == 0)
        delta_x = 1e30;
    else
        delta_x = fabs(1.0 / ray.ray_dir.x);
    if (ray.ray_dir.y == 0)
        delta_y = 1e30;
    else
        delta_y = fabs(1.0 / ray.ray_dir.y);
    if (ray.ray_dir.x < 0)
    {
        step_x = -1;
        side_dist_x = (px - map_x) * delta_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - px) * delta_x;
    }
    if (ray.ray_dir.y < 0)
    {
        step_y = -1;
        side_dist_y = (py - map_y) * delta_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - py) * delta_y;
    }
    hit = 0;
    while (hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_y;
            map_y += step_y;
            side = 1;
        }
        if (map_x < 0 || map_x >= g->map->map_width || map_y < 0 || map_y >= g->map->map_height)
            return (0);
        if (g->map->map[map_y][map_x] == 'D' || g->map->map[map_y][map_x] == '1'|| g->map->map[map_y][map_x] == 'd')
            hit = 1;
    }
    if (side == 0)
        t = (map_x - px + (1.0 - step_x) / 2.0) / ray.ray_dir.x;
    else
        t = (map_y - py + (1.0 - step_y) / 2.0) / ray.ray_dir.y;
    if (t > USE_RANGE || t < 0)
        return 0;
    tile = g->map->map[map_y][map_x];
    if (tile == 'D' || tile == 'd')
    {
        set_vector(&g->map->door_pos, (double)map_x, (double)map_y);
        return (1);
    }
    else
        return (0);
}

void door_animation(t_game *game)
{
    int posx;
    int posy;

    if(interact_cast(game))
    {
        posx = (int)game->map->door_pos.x;
        posy = (int)game->map->door_pos.y;
        if (game->map->map[posy][posx] == 'd')
            game->map->map[posy][posx] = 'D';
        else if (game->map->map[posy][posx] == 'D')
            game->map->map[posy][posx] = 'd';
    }
    else
        return;
}