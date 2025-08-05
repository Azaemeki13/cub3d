/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:15:42 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/05 12:07:44 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double ray_casting(int x, t_player player)
{
    int x = 0;
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
        
        x++;
    }

}