/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_moves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:51:32 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/22 14:19:08 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	collision_detection(t_game *game, double new_x, double new_y)
{
	int		map_x;
	int		map_y;
	t_door	*door;
	char	tile;

	map_x = (int)new_x;
	map_y = (int)new_y;
	tile = game->map->map[map_y][map_x];
	if (map_x < 0 || map_x >= game->map->map_width || map_y < 0
		|| map_y >= game->map->map_height) // out of bounds
		return (false);
	if (tile == '1') // hit a wall
		return (false);
	else if (tile == 'D')
	{
		door = door_at(game, map_x, map_y);
		if (!door || door->frac < 0.5)
			return (false);
	}
	return (true);
}

void	pause_screen(t_game *game)
{
	int	cx;
	int	cy;

	cx = WIN_WIDTH / 2;
	cy = WIN_HEIGHT / 2;
	game->game_pause = !game->game_pause;
	if (game->game_pause)
		mlx_mouse_show(game->mlx, game->win);
	else
	{
		mlx_mouse_hide(game->mlx, game->win);
		mlx_mouse_move(game->mlx, game->win, cx, cy);
		game->last_mouse_x = cx;
	}
}

int	on_key_press(int keycode, t_game *game)
{
	if (game->game_pause)
		return (0);
	if (keycode == W)
		game->buttons.w = 1;
	if (keycode == S)
		game->buttons.s = 1;
	if (keycode == A)
		game->buttons.q = 1;
	if (keycode == D)
		game->buttons.d = 1;
	if (keycode == ROTATE_LEFT)
		game->buttons.rotate_left = 1;
	if (keycode == ROTATE_RIGHT)
		game->buttons.rotate_right = 1;
	if (keycode == ESCAPE_KEY)
		return (close_window_x(game));
	return (0);
}

int	on_key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->buttons.w = 0;
	if (keycode == S)
		game->buttons.s = 0;
	if (keycode == A)
		game->buttons.q = 0;
	if (keycode == D)
		game->buttons.d = 0;
	if (keycode == ROTATE_LEFT)
		game->buttons.rotate_left = 0;
	if (keycode == ROTATE_RIGHT)
		game->buttons.rotate_right = 0;
	if (keycode == P)
		pause_screen(game);
	if (keycode == SPACE)
		door_use(game);
	if (keycode == M)
		game->show_minimap = !game->show_minimap;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.5;
	new_y = 0;
	key_hook_helper(keycode, game, move_speed, new_y);
	key_hook_helper2(keycode, game, move_speed);
	if (keycode == A)
	{
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
	return (0);
}
