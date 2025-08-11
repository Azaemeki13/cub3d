/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:58:49 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/11 16:14:37 by chsauvag         ###   ########.fr       */
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
    int			wall_dir;
    int ceiling_color;
    int floor_color;

    game = (t_game *)param;
    
    if (!game->img)
    {
        game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
        game->addr = mlx_get_data_addr(game->img,
                &game->bits_per_pixel, &game->line_length, &game->endian);
    }
    ceiling_color = create_rgb_color(game->map->ceiling->r, game->map->ceiling->g, game->map->ceiling->b);
    floor_color = create_rgb_color(game->map->floor->r, game->map->floor->g, game->map->floor->b);
    //printf("Ceiling color: %d, Floor color: %d\n", ceiling_color, floor_color);
    ft_memset(game->addr, 0, WIN_HEIGHT * game->line_length);
    x = 0;
    while (x < WIN_WIDTH)
    {
        perp_dist = ray_casting(x, game->player, &wall_dir, game);
        range = calculate_draw_range(perp_dist);
        color = get_wall_color(wall_dir);
        color = get_shade_color(color, perp_dist);

        draw_vertical_line(game, x, 0, range.start - 1, ceiling_color); // ceiling
        draw_vertical_line(game, x, range.start, range.end, color); //wall
        draw_vertical_line(game, x, range.end + 1, WIN_HEIGHT - 1, floor_color); // floor
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

int get_wall_direction(int side, int step_x, int step_y)
{
    if (side == 0) 
    {
        if (step_x > 0)
            return EAST; //
        else
            return WEST;
    }
    else
    {
        if (step_y > 0)
            return SOUTH;
        else
            return NORTH;
    }
}
