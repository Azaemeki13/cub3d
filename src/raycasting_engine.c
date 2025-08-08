/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:15:42 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/08 09:08:29 by cauffret         ###   ########.fr       */
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

int world_map[MAP_WIDTH][MAP_HEIGHT] = {
    {1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1},
};

double ray_casting(int x, t_player *player)
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
        if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
        {
            hit = 1;
            break;
        }
        if (world_map[map_y][map_x] > 0)
            hit = 1;
    }
    if (side == 0)
        perp_wall_dist = (map_x - player->player_pos->x + (1 - step_x) / 2) / ray.ray_dir.x;
    else
        perp_wall_dist = (map_y - player->player_pos->y + (1 - step_y) / 2) / ray.ray_dir.y;
    return perp_wall_dist;
}

// wall height : line_height = (int)(WIN_HEIGHT / perp_wall_dist);

t_drawrange calculate_draw_range(double perp_wall_dist)
{
    t_drawrange range;

    if (perp_wall_dist <= 0)
    {
        range.start = 0;
        range.end = WIN_HEIGHT - 1;
        range.height = WIN_HEIGHT;
        return range; // Return the range structure, not WIN_HEIGHT
    }
    // calculate the height of the wall line
    range.height = (int)(WIN_HEIGHT / perp_wall_dist);

    // calculate the start and end of the wall line
    range.start = -range.height / 2 + WIN_HEIGHT / 2;
    if (range.start < 0) //out of screen bounds
        range.start = 0;
    range.end = range.height / 2 + WIN_HEIGHT / 2;
    if (range.end >= WIN_HEIGHT) //out of screen bounds
        range.end = WIN_HEIGHT - 1;

    //printf("Draw range: start = %d, end = %d, height = %d\n", range.start, range.end, range.height);
    return range;
}

void draw_vertical_line(t_game *game_data, int x, int start, int end, int color)
{
    int y;
    char *dst;
    
    y = start;
    while (y <= end)
    {
        dst = game_data->addr + (y * game_data->line_length + x * (game_data->bits_per_pixel / 8)); // frame buffer address calculation for rendering
        *(unsigned int*)dst = color; // set pixel color
        y++;
    }
}