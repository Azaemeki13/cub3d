/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:51:29 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/12 13:12:03 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_pow2(int n)
{
    return (n > 0 && (n & ( n - 1)) == 0);
}

t_text *get_wall_text(int wall_dir, t_game **game)
{
    t_map *map;

    map = (*game)->map;
    if (wall_dir == NORTH)
        return(map->no);
    else if (wall_dir == EAST)
        return(map->ea);
    else if (wall_dir == SOUTH)
        return(map->so);
    else if (wall_dir == WEST)
        return(map->we);
    return (NULL);
}

void set_bytespp(t_game **game)
{
    t_map *map;
    
    map = (*game)->map;
    map->no->bytes_pp = map->no->bpp / 8;
    map->ea->bytes_pp = map->ea->bpp / 8;
    map->so->bytes_pp = map->so->bpp / 8;
    map->we->bytes_pp = map->we->bpp / 8;
}

void draw_textures(t_game **game, int x, int start, int end, t_text *text )
{
    int height;
    int h;
    double step;
    double tex_pos;
    int y;
    int tex_y;
    int tex_x;
    char *dest;
    char *src;
    unsigned int texel;
    unsigned int bytes_pp;
    

    bytes_pp = ((*game)->bits_per_pixel / 8);
    // mapping x axis of the texture. 
    tex_x = floor((*game)->wall_x * text->width);
    if ((*game)->side_out == 0 && (*game)->ray_dir.x > 0)
        tex_x = text->width - tex_x - 1;
    else if ((*game)->side_out == 1 && (*game)->ray_dir.y < 0)
        tex_x = text->width - tex_x - 1;
    if (tex_x < 0)
        tex_x = 0;
    else if (tex_x >= text->width)
        tex_x = text->width - 1;
    if (start > end)
        return;
    y = start;
    // step 1 how fast do I walk the texture, scan range
    height = end - start + 1;
    h = text->height;
    if (height <= 0)
        return;
    step = ( double)h / (double)height;
    // step 2 where to start in the texture pos (center it)
    tex_pos = (start - WIN_HEIGHT / 2.0 + height / 2.0)  *step;
    //step 3 loop and draw texels (texture pixel ?)
    while (y <= end)
    {
        tex_y = (int)tex_pos;
        if (is_pow2(h))
            tex_y &= (h - 1);
        else
        {
            if (tex_y < 0)
                tex_y = 0;
            else if (tex_y >= h)
                tex_y = h - 1;
        }
        src = text->addr + tex_y * text->sl + tex_x * text->bytes_pp;
        dest = (*game)->addr + y * (*game)->line_length + x * bytes_pp;
        texel = *(unsigned int *)src;
        *(unsigned int *)dest = texel;
        tex_pos += step;
        y++;
    }
}