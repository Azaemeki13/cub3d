/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:47:16 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/11 14:42:41 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int create_rgb_color(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

int get_shade_color(int base_color, double distance)
{
    int r = (base_color >> 16) & 0xFF;
    int g = (base_color >> 8) & 0xFF;
    int b = base_color & 0xFF;
    
    (void) distance;
    //double shade_factor = 1.0 / (1.0 + distance * distance * 0.1);
    
    /*r = (int)(r * shade_factor);
    g = (int)(g * shade_factor);
    b = (int)(b * shade_factor);*/
    
    return create_rgb_color(r, g, b);
}

int get_wall_color(int wall_dir) ////////////to be replaced with texture later
{
    switch (wall_dir)
    {
        case NORTH:
            return create_rgb_color(255, 0, 0);
        case EAST:
            return create_rgb_color(0, 255, 0);
        case SOUTH:
            return create_rgb_color(0, 0, 255);
        case WEST:
            return create_rgb_color(255, 255, 0);
        default:
            return create_rgb_color(255, 255, 255);
    }
}
