/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reticle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:18:51 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/19 16:14:04 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_reticle(t_game **game, int thick, int size)
{
    int cx;
    int cy;
    int x;
    int y;
    int gap;
    int x_start;
    int x_end;
    int y_start;
    int y_end;
    
    gap = 3;
    cx = WIN_WIDTH / 2;
    cy = WIN_HEIGHT / 2;
    x_start = cx - (thick / 2);
    x_end = cx + (thick - 1) / 2;
    y_start = cy - (thick / 2);
    y_end = cy + (thick - 1) / 2;
    y = cy - size;
    if (size <= gap)
        return;
    // top half of arm
    while (y <= (cy - gap - 1))
    {
        x = x_start;
        while  (x <= x_end)
            draw_minimap_pixel((*game), x++, y ,create_rgb_color(255, 0, 0));
        y++;
    }
    // middle now
    y = y_start;
    while ( y <= y_end)
    {
        x = cx - size;
        while (x <= cx - gap - 1)
            draw_minimap_pixel((*game), x++, y ,create_rgb_color(255, 0, 0));
        x = cx + gap + 1;
        while (x  <= (cx + size))
            draw_minimap_pixel((*game), x++, y ,create_rgb_color(255, 0, 0));
        y++;
    }
    // bottom now
    y = cy + gap + 1;
    while (y <= (cy + size))
    {
        x = x_start;
        while  (x <= x_end)
            draw_minimap_pixel((*game), x++, y ,create_rgb_color(255, 0, 0));
        y++;
    }
}
