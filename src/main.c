/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:13:42 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/07 13:57:40 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main()
{
    t_game game_data;

    ft_memset(&game_data, 0, sizeof(t_game));

    game_data.mlx = mlx_init();
    if (!game_data.mlx)
        return (1);
    
    // Initialize player
    game_data.player.player_pos.x = 6.0;
    game_data.player.player_pos.y = 3.0;
    game_data.player.vector_dir.x = -1.0;
    game_data.player.vector_dir.y = 0.0;
    game_data.player.camera_plane.x = 0.0;
    game_data.player.camera_plane.y = 0.66;
    
    create_window(&game_data);
    if (!game_data.win)
        return (1);

    mlx_loop_hook(game_data.mlx, render_frame, &game_data);
    mlx_hook(game_data.win, 2, 1L<<0, key_hook, &game_data);
    mlx_loop(game_data.mlx);
    
    return 0;
}