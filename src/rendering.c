/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:58:49 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/19 17:28:52 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	render_frame(void *param)
{
    t_game		*game;
    int			x;
    double		perp_dist;
    // int			color;
    t_text   *tex;
    int			wall_dir;
    int ceiling_color;
    int floor_color;
    int start;
    int end;

    game = (t_game *)param;
    game_update(game);
    if (!game->img)
    {
        game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
        game->addr = mlx_get_data_addr(game->img,
                &game->bits_per_pixel, &game->line_length, &game->endian);
    }
    set_bytespp(&game);
    ceiling_color = create_rgb_color(game->map->ceiling->r, game->map->ceiling->g, game->map->ceiling->b);
    floor_color = create_rgb_color(game->map->floor->r, game->map->floor->g, game->map->floor->b);
    ft_memset(game->addr, 0, WIN_HEIGHT * game->line_length);
    x = 0;
    while (x < WIN_WIDTH)
    {
        perp_dist = ray_casting(x, game->player, &wall_dir, game, &game->wall_x);
        game->range = calculate_draw_range(perp_dist, game);
        start = game->range.start;
        end = game->range.end; 
        if (start < 0)
            start = 0;
        if (end >= WIN_HEIGHT)
            end = WIN_HEIGHT - 1;
        if (start > 0)
            draw_vertical_line(game, x, 0, start - 1, ceiling_color);
        tex = get_wall_text(wall_dir, &game);
        if (start <= end)
            draw_textures(&game, x, start, end, tex);
        if (end < WIN_HEIGHT - 1)
            draw_vertical_line(game, x, end + 1, WIN_HEIGHT - 1, floor_color);
        // calculate tex_x
        
        //color = get_wall_color(wall_dir);
        // color = get_shade_color(color, perp_dist);
        x++;
    }
    if (game->show_minimap)
        draw_minimap(game);
    draw_reticle(&game, 5, 10);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

int get_wall_direction(int side, int step_x, int step_y)
{
    if (side == 0) 
    {
        if (step_x > 0)
            return EAST;
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

int game_update(t_game *game)
{
    t_keymap keys;
    double old_dir_x;
    double old_plane_x;
    double rotation_speed = 0.1;
    
    keys = game->buttons;
    doors_update(game, 0.0);
    if (keys.w)
        move_forward(game);
    if (keys.s)
        move_backwards(game);
    if (keys.q)
        move_left(game);
    if (keys.d)
        move_right(game);
    if (keys.rotate_left)
    {
        old_dir_x = game->player->vector_dir->x;
        game->player->vector_dir->x = game->player->vector_dir->x * cos(-rotation_speed) - game->player->vector_dir->y * sin(-rotation_speed);
        game->player->vector_dir->y = old_dir_x * sin(-rotation_speed) + game->player->vector_dir->y * cos(-rotation_speed);
    
        old_plane_x = game->player->camera_plane->x;
        game->player->camera_plane->x = game->player->camera_plane->x * cos(-rotation_speed) - game->player->camera_plane->y * sin(-rotation_speed);
        game->player->camera_plane->y = old_plane_x * sin(-rotation_speed) + game->player->camera_plane->y * cos(-rotation_speed);
    }
    if (keys.rotate_right)
    {
        old_dir_x = game->player->vector_dir->x;
        game->player->vector_dir->x = game->player->vector_dir->x * cos(rotation_speed) - game->player->vector_dir->y * sin(rotation_speed);
        game->player->vector_dir->y = old_dir_x * sin(rotation_speed) + game->player->vector_dir->y * cos(rotation_speed);
    
        old_plane_x = game->player->camera_plane->x;
        game->player->camera_plane->x = game->player->camera_plane->x * cos(rotation_speed) - game->player->camera_plane->y * sin(rotation_speed);
        game->player->camera_plane->y = old_plane_x * sin(rotation_speed) + game->player->camera_plane->y * cos(rotation_speed);
    }
    return(0);
}
