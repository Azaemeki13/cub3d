/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:40:22 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/07 12:13:42 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void create_window(t_game *game)
{
    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    if(game->win == NULL)
    {
        error_msg("Failed to create a new window");
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        return;
    }
    mlx_key_hook(game->win, close_window_hook, game);
    mlx_hook(game->win, 17, 0, close_window_x, game);
    // Remove mlx_loop from here since it's called in main
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