/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:15:42 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/04 16:41:25 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double ray_casting(int x, t_player player)
{
    int x = 0;
    double camera_x;

    while(x < WIN_WIDTH)
    {
        //calculate camera_x [-1; 1]
        camera_x = 2 * x / (double)WIN_WIDTH - 1; // that's 2 * 0 / 1024 - 1 = -1.0 (far left) if camera_x = 0
    
            //calculate ray direction
            
            //curent tile ?
            
        //delta distances
        delta.x = fabs(1 / ray->ray_dir.x);
        delta.y = fabs(1 / ray->ray_dir.y);
        x++;
    }

}