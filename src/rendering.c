/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:58:49 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/07 13:49:51 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	render_frame(void *param)
{
    t_game		*game;
    int			x;
    double		perp_dist;
    t_drawrange	range;
    int			color;
    int			base_color;

    game = (t_game *)param;
    
    if (!game->img)
    {
        game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
        game->addr = mlx_get_data_addr(game->img,
                &game->bits_per_pixel, &game->line_length, &game->endian);
    }
    ft_memset(game->addr, 0, WIN_HEIGHT * game->line_length);
    x = 0;
    while (x < WIN_WIDTH)
    {
        perp_dist = ray_casting(x, game->player);  // Use game->player instead of local variable
        range = calculate_draw_range(perp_dist);
        base_color = create_rgb_color(255, 100, 50);
        color = get_shade_color(base_color, perp_dist);
        draw_vertical_line(game, x, range.start, range.end, color);
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}
