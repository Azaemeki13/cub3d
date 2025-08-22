/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 11:22:53 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/19 16:44:57 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.05;
	new_x = game->player->player_pos->x + game->player->vector_dir->x
		* move_speed;
	new_y = game->player->player_pos->y + game->player->vector_dir->y
		* move_speed;
	if (collision_detection(game, new_x, new_y))
	{
		game->player->player_pos->x = new_x;
		game->player->player_pos->y = new_y;
	}
}

void	move_backwards(t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.05;
	new_x = game->player->player_pos->x - game->player->vector_dir->x
		* move_speed;
	new_y = game->player->player_pos->y - game->player->vector_dir->y
		* move_speed;
	if (collision_detection(game, new_x, new_y))
	{
		game->player->player_pos->x = new_x;
		game->player->player_pos->y = new_y;
	}
}

void	move_left(t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.05;
	new_x = game->player->player_pos->x + game->player->vector_dir->y
		* move_speed;
	new_y = game->player->player_pos->y - game->player->vector_dir->x
		* move_speed;
	if (collision_detection(game, new_x, new_y))
	{
		game->player->player_pos->x = new_x;
		game->player->player_pos->y = new_y;
	}
}

void	move_right(t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.05;
	new_x = game->player->player_pos->x - game->player->vector_dir->y
		* move_speed;
	new_y = game->player->player_pos->y + game->player->vector_dir->x
		* move_speed;
	if (collision_detection(game, new_x, new_y))
	{
		game->player->player_pos->x = new_x;
		game->player->player_pos->y = new_y;
	}
}
