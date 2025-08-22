/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:13:42 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/22 15:07:26 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void welcome_message(void)
{
    ft_putstr_fd("WELCOME TO CUB3D!\n", 1);
    ft_putstr_fd("Press 'ESC' to exit.\n", 1);
    ft_putstr_fd("Use 'W', 'A', 'S', 'D' to move.\n", 1);
    ft_putstr_fd("Use mouse or 'LEFT/RIGHT' to look around.\n", 1);
    ft_putstr_fd("Press 'M' to toggle ON/OFF the minimap.\n", 1);
    ft_putstr_fd("Press 'SPACE' to open and close doors.\n", 1);
    ft_putstr_fd("Press 'P' to pause.\n", 1);
}

static void main_helper(t_game **game_data, char *path)
{
    if (!validate_init(game_data, path))
    {
        error_msg("Failed to initialise.\n");
        free_game_complete(game_data);
        exit(1);
    }
}

int main(int argc, char **argv)
{
    t_game *game_data;
    char *path;

    game_data = NULL;
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
    main_helper(&game_data, path);
    create_window(game_data);
    welcome_message();
    mlx_mouse_hide(game_data->mlx, game_data->win);
    mlx_hook(game_data->win, 2, 1L<<0, on_key_press, game_data);
    mlx_hook(game_data->win, 3, 1L<<1, on_key_release,  game_data);
    mlx_hook(game_data->win, 6, 1L<<6, on_mouse_move, game_data);
    mlx_loop_hook(game_data->mlx, render_frame, game_data);
    mlx_loop(game_data->mlx);
    return 0;
}
