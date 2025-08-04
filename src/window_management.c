/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:40:22 by chsauvag          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/04 13:17:31 by chsauvag         ###   ########.fr       */
=======
/*   Updated: 2025/08/04 12:53:03 by cauffret         ###   ########.fr       */
>>>>>>> f9e6739bd94da75f6a429cd6fe5725a04eed3f40
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void create_window()
{
    t_game game;

    game.mlx = mlx_init();
    if(game.mlx == NULL)
    {
        error_msg("Failed to initialize MLX");
        return;
    }
    game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    if(game.win == NULL)
    {
        error_msg("Failed to create a new window");
        mlx_destroy_display(game.mlx);
        free(game.mlx);
        return;
    }
    mlx_key_hook(game.win, close_window_hook, &game);
    mlx_hook(game.win, 17, 0, close_window_x, &game);
    mlx_loop(game.mlx);
}

int close_window_hook(int keycode, t_game *game) // ESCAPE key
{
    if (keycode == ESCAPE_KEY)
    {
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        exit(0);
    }
    return 0;
}

int close_window_x(t_game *game) //(x) button
{
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    exit(0);
    return (0);
}