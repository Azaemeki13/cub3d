/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_moves_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:09:32 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 14:20:02 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void key_hook_helper(int keycode, t_game *game, double move_speed, double new_y)
{
    double new_x;

    new_x = 0;
    if(keycode == W)
    {
        new_x = game->player->player_pos->x + game->player->vector_dir->x * move_speed;
        new_y = game->player->player_pos->y + game->player->vector_dir->y * move_speed;
        if (collision_detection(game, new_x, new_y))
        {
            game->player->player_pos->x = new_x;
            game->player->player_pos->y = new_y;
        }
    }
    if(keycode == S)
    {
        new_x = game->player->player_pos->x - game->player->vector_dir->x * move_speed;
        new_y = game->player->player_pos->y - game->player->vector_dir->y * move_speed;
        if (collision_detection(game, new_x, new_y))
        {
            game->player->player_pos->x = new_x;
            game->player->player_pos->y = new_y;
        }
    }
}

void key_hook_helper2(int keycode, t_game *game, double move_speed)
{
    double new_x;
    double new_y;

    new_x = 0;
    new_y = 0;
    if(keycode == D)
    {
        new_x = game->player->player_pos->x - game->player->vector_dir->y * move_speed;
        new_y = game->player->player_pos->y + game->player->vector_dir->x * move_speed;
        if (collision_detection(game, new_x, new_y))
        {
            game->player->player_pos->x = new_x;
            game->player->player_pos->y = new_y;

        }
    }
}
