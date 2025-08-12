/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:27:58 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/12 11:16:41 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_minimap_pixel(t_game *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
    dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_minimap_square(t_game *game, int start_x, int start_y, int size, int color)
{
    int x;
    int y;

    y = start_y;
    while (y < start_y + size)
    {
        x = start_x;
        while (x < start_x + size)
        {
            draw_minimap_pixel(game, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_minimap(t_game *game)
{
    int map_x;
    int map_y;
    int screen_x;
    int screen_y;
    double player_x;
    double player_y;
    int player_screen_x;
    int player_screen_y;

    map_y = 0;
    while (map_y < game->map->map_height)
    {
        map_x = 0;
        while (map_x < game->map->map_width)
        {
            screen_x = MINIMAP_OFFSET_X + map_x * MINIMAP_TILE_SIZE;
            screen_y = MINIMAP_OFFSET_Y + map_y * MINIMAP_TILE_SIZE;
            
            if (game->map->map[map_y][map_x] == '1')
                draw_minimap_square(game, screen_x, screen_y, MINIMAP_TILE_SIZE, create_rgb_color(0, 0, 0));
            else if (game->map->map[map_y][map_x] == '0' || game->map->map[map_y][map_x] == 'N' || 
                     game->map->map[map_y][map_x] == 'S' || game->map->map[map_y][map_x] == 'E' || 
                     game->map->map[map_y][map_x] == 'W')
                draw_minimap_square(game, screen_x, screen_y, MINIMAP_TILE_SIZE, create_rgb_color(0, 0, 255));
            
            map_x++;
        }
        map_y++;
    }
    player_x = game->player->player_pos->x;
    player_y = game->player->player_pos->y;
    
    player_screen_x = MINIMAP_OFFSET_X + (player_x * MINIMAP_TILE_SIZE);
    player_screen_y = MINIMAP_OFFSET_Y + (player_y * MINIMAP_TILE_SIZE);

    int dot_size = MINIMAP_TILE_SIZE;
    draw_minimap_square(game, player_screen_x, player_screen_y, dot_size, create_rgb_color(255, 0, 0));
}