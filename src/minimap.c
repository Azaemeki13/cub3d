/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:27:58 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/21 16:51:14 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int is_inside_circle(int x, int y, int center_x, int center_y, int radius)
{
    int dx = x - center_x;
    int dy = y - center_y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

void draw_minimap_pixel(t_game *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
    dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_minimap_pixel_circle(t_game *game, int x, int y, int color, int center_x, int center_y, int radius)
{
    char *dst;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
    if (!is_inside_circle(x, y, center_x, center_y, radius))
        return;
    dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_minimap_square_circle(t_game *game, int start_x, int start_y, int size, int color, int center_x, int center_y, int radius)
{
    int x;
    int y;

    y = start_y;
    while (y < start_y + size)
    {
        x = start_x;
        while (x < start_x + size)
        {
            draw_minimap_pixel_circle(game, x, y, color, center_x, center_y, radius);
            x++;
        }
        y++;
    }
}

void draw_circle_border(t_game *game, int center_x, int center_y, int radius, int thickness)
{
    int y = center_y - radius - thickness;
    int x;
    int distance;
    int outer_radius = radius + thickness;
    int inner_radius = radius;

    while (y <= center_y + radius + thickness)
    {
        x = center_x - radius - thickness;
        while (x <= center_x + radius + thickness)
        {
            distance = (x - center_x) * (x - center_x) + (y - center_y) * (y - center_y);
            if (distance <= outer_radius * outer_radius && distance > inner_radius * inner_radius)
                draw_minimap_pixel_circle(game, x, y, create_rgb_color(255, 255, 255), center_x, center_y, radius + thickness);
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
    int minimap_size = 20;
    int minimap_radius = (minimap_size * MINIMAP_TILE_SIZE) / 2;
    int center_x = MINIMAP_OFFSET_X + minimap_radius;
    int center_y = MINIMAP_OFFSET_Y + minimap_radius;
    int start_map_x, start_map_y;
    int end_map_x, end_map_y;

    player_x = game->player->player_pos->x;
    player_y = game->player->player_pos->y;
    
    start_map_x = (int)player_x - minimap_size / 2;
    start_map_y = (int)player_y - minimap_size / 2;
    end_map_x = start_map_x + minimap_size;
    end_map_y = start_map_y + minimap_size;
    draw_circle_border(game, center_x, center_y, minimap_radius, 2);
    map_y = start_map_y;
    while (map_y < end_map_y)
    {
        map_x = start_map_x;
        while (map_x < end_map_x)
        {
            screen_x = MINIMAP_OFFSET_X + (map_x - start_map_x) * MINIMAP_TILE_SIZE;
            screen_y = MINIMAP_OFFSET_Y + (map_y - start_map_y) * MINIMAP_TILE_SIZE;      
            if (map_x < 0 || map_x >= game->map->map_width || 
                map_y < 0 || map_y >= game->map->map_height)
                draw_minimap_square_circle(game, screen_x, screen_y, MINIMAP_TILE_SIZE, create_rgb_color(64, 64, 64), center_x, center_y, minimap_radius);
            else if (game->map->map[map_y][map_x] == '1')
                draw_minimap_square_circle(game, screen_x, screen_y, MINIMAP_TILE_SIZE, create_rgb_color(0, 0, 0), center_x, center_y, minimap_radius);
            else if (game->map->map[map_y][map_x] == 'D' || game->map->map[map_y][map_x] == 'd')
                draw_minimap_square_circle(game, screen_x, screen_y, MINIMAP_TILE_SIZE, create_rgb_color(25, 210, 250), center_x, center_y, minimap_radius);
            else if (game->map->map[map_y][map_x] == ' ')
                draw_minimap_square_circle(game, screen_x, screen_y, MINIMAP_TILE_SIZE, create_rgb_color(128, 128, 128), center_x, center_y, minimap_radius);
            else if (game->map->map[map_y][map_x] == '0' || game->map->map[map_y][map_x] == 'N' || 
                     game->map->map[map_y][map_x] == 'S' || game->map->map[map_y][map_x] == 'E' || 
                     game->map->map[map_y][map_x] == 'W')
                draw_minimap_square_circle(game, screen_x, screen_y, MINIMAP_TILE_SIZE, create_rgb_color(200, 200, 200), center_x, center_y, minimap_radius);
            else
                draw_minimap_square_circle(game, screen_x, screen_y, MINIMAP_TILE_SIZE, create_rgb_color(128, 128, 128), center_x, center_y, minimap_radius);
            
            map_x++;
        }
        map_y++;
    }
    player_screen_x = center_x - MINIMAP_TILE_SIZE / 2;
    player_screen_y = center_y - MINIMAP_TILE_SIZE / 2;
    draw_minimap_square_circle(game, player_screen_x, player_screen_y, MINIMAP_TILE_SIZE, create_rgb_color(255, 0, 0), center_x, center_y, minimap_radius);
}
