/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:40:22 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/22 12:03:01 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (game->win == NULL)
	{
		error_msg("Failed to create a new window");
		free_game_complete(&game);
		exit(1);
	}
	mlx_key_hook(game->win, close_window_hook, game);
	mlx_hook(game->win, 17, 0, close_window_x, game);
}

int	close_window_hook(int keycode, t_game *game)
{
	if (keycode == ESCAPE_KEY)
	{
		free_game_complete(&game);
		exit(0);
	}
	return (0);
}

int	close_window_x(t_game *game)
{
	free_game_complete(&game);
	exit(0);
	return (0);
}
