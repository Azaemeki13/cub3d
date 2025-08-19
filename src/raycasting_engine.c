/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:15:42 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/19 15:25:24 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*double ray_casting(int x, t_player player)
{
    double camera_x;
    int wall_hit = 0;

    while(x < WIN_WIDTH)
    {
        ///////////////////// RAY DIRECTION CALCULATIONS ///////////////////////
        camera_x = 2 * x / (double)WIN_WIDTH - 1; // that's 2 * 0 / 1024 - 1 = -1.0 (far left) if camera_x = 0
        
        t_ray ray;
        ray->ray_dir.x = player.dir.x + player.plane.x * camera_x; // ray direction in x ray_dir = center_direction + spread_left_right
        ray->ray_dir.y = player.dir.y + player.plane.y * camera_x;
        
        ray.map.x = (int)player.pos.x; //takes the current floating point and converts
        ray.map.y = (int)player.pos.y; //it to an integer to indicate the current tile the character is standing on

        delta.x = fabs(1 / ray->ray_dir.x); //delta x is the distance to the next vertical line
        delta.y = fabs(1 / ray->ray_dir.y); //delta y is the distance to the next horizontal line

        /////////////////// STEP DIRECTIONS CALCULATIONS //////////////////////
        t_vector side_dist;

        if(ray.ray_dir.x < 0) //left
        {
            step_dir_x = -1; //if ray direction is negative, we step left
            side_dist.x = (player.pos.x - ray.map.x) * delta.x;
            //side is the distance to hit the edge of the current tile to the left
        }
        else if (ray.ray_dir.x > 0) //right
        {
            step_dir_x = 1;
            side_dist.x = (ray.map.x + 1.0 - player.pos.x) * delta.x; 
        }
        
        if(ray.ray_dir.y < 0) //up
        {
            step_dir_y = -1;
            side_dist.y = (player.pos.y - ray.map.y) * delta.y;
        }
        else if (ray.ray_dir.y > 0) //down
        {
            step_dir_y = 1;
            side_dist.y = (ray.map.y + 1.0 - player.pos.y) * delta.y;
        }
        
        /////////////////// DDA LOOP //////////////////////
    int hit = 0;
    int side = 0;
    while (hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_y;
            map_y += step_y;
            side = 1;
        }
        if (world_map[map_x][map_y] > 0)
            hit = 1;
    }

    double perp_wall_dist;
    if (side == 0)
        perp_wall_dist = (map_x - player.pos.x + (1 - step_x) / 2) / ray.ray_dir.x;
    else
        perp_wall_dist = (map_y - player.pos.y + (1 - step_y) / 2) / ray.ray_dir.y;

    printf("Column %d hit wall at distance: %f\n", x, perp_wall_dist);
    return perp_wall_dist;
}*/

double ray_casting(int x, t_player *player, int *wall_direction, t_game *game, double *wall_x)
{
        double	camera_x;
        t_ray	ray;
        int		map_x;
        int		map_y;
        double	delta_x;
        double	delta_y;
        int		step_x;
        int		step_y;
        double	side_dist_x;
        double	side_dist_y;
        int		hit;
        int		side;
        double hit_x;
        double hit_y;
        double	perp_wall_dist;

    camera_x = 2 * x / (double)WIN_WIDTH - 1;
    ray.ray_dir.x = player->vector_dir->x + player->camera_plane->x * camera_x;
    ray.ray_dir.y = player->vector_dir->y + player->camera_plane->y * camera_x;
    
    map_x = (int)player->player_pos->x;
    map_y = (int)player->player_pos->y;

    if (ray.ray_dir.x == 0)
        delta_x = 1e30;
    else
        delta_x = fabs(1 / ray.ray_dir.x);
    if (ray.ray_dir.y == 0)
        delta_y = 1e30;
    else
        delta_y = fabs(1 / ray.ray_dir.y);

    if (ray.ray_dir.x < 0) //left
    {
        step_x = -1;
        side_dist_x = (player->player_pos->x - map_x) * delta_x;
    }
    else //right
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - player->player_pos->x) * delta_x;
    }
    if (ray.ray_dir.y < 0) //up
    {
        step_y = -1;
        side_dist_y = (player->player_pos->y - map_y) * delta_y;
    }
    else //down
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - player->player_pos->y) * delta_y;
    }
    hit = 0;
    while (hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_y;
            map_y += step_y;
            side = 1;
        }
        if (map_x < 0 || map_x >= game->map->map_width || map_y < 0 || map_y >= game->map->map_height)        {
            hit = 1;
            break;
        }
        if (game->map->map[map_y][map_x] == '1' || game->map->map[map_y][map_x] == 'D')
        {
            game->hit_tile = game->map->map[map_y][map_x];
            hit = 1;
        }
    }
    *wall_direction = get_wall_direction(side, step_x, step_y);
    
    if (side == 0)
        perp_wall_dist = (map_x - player->player_pos->x + (1 - step_x) / 2) / ray.ray_dir.x;
    else
        perp_wall_dist = (map_y - player->player_pos->y + (1 - step_y) / 2) / ray.ray_dir.y;
    hit_x = game->player->player_pos->x + perp_wall_dist * ray.ray_dir.x;
    hit_y = game->player->player_pos->y + perp_wall_dist * ray.ray_dir.y;
    if (side == 0)
        *wall_x = hit_y;
    else
        *wall_x = hit_x;
    *wall_x = *wall_x - floor(*wall_x);
    game->side_out = side;
    game->ray_dir.x = ray.ray_dir.x;
    game->ray_dir.y = ray.ray_dir.y;
    return perp_wall_dist;
}

// wall height : line_height = (int)(WIN_HEIGHT / perp_wall_dist);

t_drawrange calculate_draw_range(double perp_wall_dist, t_game *game)
{
    t_drawrange range;

    if (perp_wall_dist <= 0)
    {
        range.start = 0;
        range.end = WIN_HEIGHT - 1;
        range.height = WIN_HEIGHT;
        return range;
    }
    // calculate the height of the wall line
    range.height = (int)(WIN_HEIGHT / perp_wall_dist);

    // calculate the start and end of the wall line
    range.start = (WIN_HEIGHT - range.height) / 2 + game->player->pitch;
    range.end = (WIN_HEIGHT + range.height) / 2 + game->player->pitch;

    return range;
}

void draw_vertical_line(t_game *game_data, int x, int start, int end, int color)
{
    int y;
    char *dst;

    if (start < 0) start = 0;
    if (end >= WIN_HEIGHT) end = WIN_HEIGHT - 1;
    if (start > end) return;
    
    y = start;
    while (y <= end)
    {
        dst = game_data->addr + (y * game_data->line_length + x * (game_data->bits_per_pixel / 8)); // frame buffer address calculation for rendering
        *(unsigned int*)dst = color; // set pixel color
        y++;
    }
}