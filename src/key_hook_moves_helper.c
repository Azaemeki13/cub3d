/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_moves_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:09:32 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/25 14:18:16 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

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

void	move_backward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

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

void	move_left(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

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

void	move_right(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

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

void	key_hook_helper(int keycode, t_game *game, double move_speed)
{
	if (keycode == W)
		move_forward(game, move_speed);
	if (keycode == S)
		move_backward(game, move_speed);
	if (keycode == A)
		move_left(game, move_speed);
	if (keycode == D)
		move_right(game, move_speed);
}
