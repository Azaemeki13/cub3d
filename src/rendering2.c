/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:17:09 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/26 13:19:56 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_left_calc(t_game *game, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->vector_dir->x;
	old_plane_x = game->player->camera_plane->x;
	game->player->vector_dir->x = game->player->vector_dir->x
		* cos(-rotation_speed) - game->player->vector_dir->y
		* sin(-rotation_speed);
	game->player->vector_dir->y = old_dir_x * sin(-rotation_speed)
		+ game->player->vector_dir->y * cos(-rotation_speed);
	game->player->camera_plane->x = game->player->camera_plane->x
		* cos(-rotation_speed) - game->player->camera_plane->y
		* sin(-rotation_speed);
	game->player->camera_plane->y = old_plane_x * sin(-rotation_speed)
		+ game->player->camera_plane->y * cos(-rotation_speed);
}

void	rotate_right_calc(t_game *game, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->vector_dir->x;
	old_plane_x = game->player->camera_plane->x;
	game->player->vector_dir->x = game->player->vector_dir->x
		* cos(rotation_speed) - game->player->vector_dir->y
		* sin(rotation_speed);
	game->player->vector_dir->y = old_dir_x * sin(rotation_speed)
		+ game->player->vector_dir->y * cos(rotation_speed);
	game->player->camera_plane->x = game->player->camera_plane->x
		* cos(rotation_speed) - game->player->camera_plane->y
		* sin(rotation_speed);
	game->player->camera_plane->y = old_plane_x * sin(rotation_speed)
		+ game->player->camera_plane->y * cos(rotation_speed);
}
