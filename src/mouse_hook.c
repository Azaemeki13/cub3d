/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:36:27 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/14 12:00:20 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int on_mouse_move(int x, int y,void *param)
{
    t_game *game = (t_game *)param;
    int dx;
    int dy;
    double angle;
    double  old_dir_x;
    double  old_plane_x;
    int center_x;
    int center_y;

    if (game->game_pause)
    {
        game->last_mouse_x = x;
        return(0); 
    }
    center_x = WIN_WIDTH / 2;
    center_y = WIN_HEIGHT / 2;
    dx = x - center_x;
    dy = y - center_y;
    if (abs(dx) < 2 && abs(dy) < 2)
        return (0);
    if (abs(dx) >= 2)
    {
        angle = dx * game->mouse_sens;
        old_dir_x = game->player->vector_dir->x;
        game->player->vector_dir->x = game->player->vector_dir->x * cos(angle) - game->player->vector_dir->y * sin(angle);
        game->player->vector_dir->y = old_dir_x * sin(angle) + game->player->vector_dir->y * cos(angle);
        old_plane_x = game->player->camera_plane->x;
        game->player->camera_plane->x = game->player->camera_plane->x * cos(angle) - game->player->camera_plane->y * sin(angle);
        game->player->camera_plane->y = old_plane_x * sin(angle) + game->player->camera_plane->y * cos(angle);
    }
    if (abs(dy) >= 2)
    {
        game->player->pitch += -dy * game->mouse_sens * 300;
        if (game->player->pitch > WIN_HEIGHT / 3)
            game->player->pitch = WIN_HEIGHT / 3;
        if (game->player->pitch < - WIN_HEIGHT / 3)
            game->player->pitch = - WIN_HEIGHT / 3;
    }
    mlx_mouse_move(game->mlx, game->win, center_x, center_y);
    return (0);
}
