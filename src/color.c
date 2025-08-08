/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:47:16 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/07 12:49:29 by chsauvag         ###   ########.fr       */
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
