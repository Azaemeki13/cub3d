/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:13:42 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/14 11:48:40 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game *game_data;
    char *path;

    if (argc != 2)
    {
        error_msg("Wrong amount of arguments.");
        exit(1);
    }
    if (!*(++argv))
    {
        error_msg("No path.");
        exit(1);
    }
    path = *argv;
    if (!validate_init(&game_data, path))
    {
        error_msg("Failed to initialise.\n");
        exit(1);
    }
    create_window(game_data);
    if (!game_data->win)
        return (1);
    mlx_mouse_hide(game_data->mlx, game_data->win);
    mlx_hook(game_data->win, 2, 1L<<0, on_key_press, game_data);
    mlx_hook(game_data->win, 3, 1L<<1, on_key_release,  game_data);
    mlx_hook(game_data->win, 6, 1L<<6, on_mouse_move, game_data);
    mlx_loop_hook(game_data->mlx, render_frame, game_data);
    mlx_loop(game_data->mlx);
    return 0;
}
