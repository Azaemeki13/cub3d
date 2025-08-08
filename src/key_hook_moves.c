/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_moves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:51:32 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/08 09:13:46 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool collision_detection(t_game *game, double new_x, double new_y)
{
    int map_x = (int)new_x;
    int map_y = (int)new_y;

    if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT) //out of bounds
        return false;
    if (game->map->content[map_y][map_x] == '1') //hit a wall
        return false;
    return true;
}

int key_hook(int keycode, t_game *game)
{
    double old_dir_x;
    double old_plane_x;
    double rotation_speed = 0.1;
    double move_speed = 0.5;

    //still needs collision detection and map boundaries + speed adjustment
    
    if(keycode == UP)
    {
        game->player->player_pos->x += game->player->vector_dir->x * move_speed;
        game->player->player_pos->y += game->player->vector_dir->y * move_speed;
    }
    if(keycode == DOWN)
    {
        game->player->player_pos->x -= game->player->vector_dir->x * move_speed;
        game->player->player_pos->y -= game->player->vector_dir->y * move_speed;
    }
    //[[cos(θ), -sin(θ)], [sin(θ), cos(θ)]]
    if (keycode == ROTATE_RIGHT)
    {
        old_dir_x = game->player->vector_dir->x;
        game->player->vector_dir->x = game->player->vector_dir->x * cos(-rotation_speed) - game->player->vector_dir->y * sin(-rotation_speed);
        game->player->vector_dir->y = old_dir_x * sin(-rotation_speed) + game->player->vector_dir->y * cos(-rotation_speed);
    
        old_plane_x = game->player->camera_plane->x;
        game->player->camera_plane->x = game->player->camera_plane->x * cos(-rotation_speed) - game->player->camera_plane->y * sin(-rotation_speed);
        game->player->camera_plane->y = old_plane_x * sin(-rotation_speed) + game->player->camera_plane->y * cos(-rotation_speed);
    }
    if (keycode == ROTATE_LEFT)
    {
        old_dir_x = game->player->vector_dir->x;
        game->player->vector_dir->x = game->player->vector_dir->x * cos(rotation_speed) - game->player->vector_dir->y * sin(rotation_speed);
        game->player->vector_dir->y = old_dir_x * sin(rotation_speed) + game->player->vector_dir->y * cos(rotation_speed);
    
        old_plane_x = game->player->camera_plane->x;
        game->player->camera_plane->x = game->player->camera_plane->x * cos(rotation_speed) - game->player->camera_plane->y * sin(rotation_speed);
        game->player->camera_plane->y = old_plane_x * sin(rotation_speed) + game->player->camera_plane->y * cos(rotation_speed);
    }
    return 0;
}