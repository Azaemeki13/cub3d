/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:51:29 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/14 10:34:05 by cauffret         ###   ########.fr       */
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

static int	clampi(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

static int	compute_tex_x(t_game *g, t_text *tex)
{
	int	tx;

	tx = (int)(g->wall_x * (double)tex->width);
	if (g->side_out == 0 && g->ray_dir.x > 0)
		tx = tex->width - tx - 1;
	else if (g->side_out == 1 && g->ray_dir.y < 0)
		tx = tex->width - tx - 1;
	return (clampi(tx, 0, tex->width - 1));
}

/* draw the textured wall slice for screen column x */
void	draw_textures(t_game **game, int x, int start, int end, t_text *tex)
{
	int		lineh;
	int		tex_x;
	int		y;
	int		tex_y;
	double	step;
	double	draw_start_u;
	double	tex_pos;
	int		scr_bpp;

	/* reject fully off-screen / degenerate */
	if (end < 0 || start >= WIN_HEIGHT)
		return ;
	lineh = (*game)->range.height;
	if (lineh <= 0)
		return ;
	/* clamp to screen */
	if (start < 0)
		start = 0;
	if (end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;
	/* horizontal mapping: wall_x -> tex_x (+ mirror fixes) */
	tex_x = compute_tex_x(*game, tex);
	/* vertical mapping: step in texture per screen pixel */
	step = (double)tex->height / (double)lineh;
	/* un-clamped top including pitch; then skip the clipped part */
	draw_start_u = -lineh / 2.0 + WIN_HEIGHT / 2.0 + (*game)->player->pitch;
	tex_pos = (start - draw_start_u) * step;
	/* precompute bytes/px for screen; textures already have bytes_pp */
	scr_bpp = (*game)->bits_per_pixel / 8;
	y = start;
	while (y <= end)
	{
		tex_y = (int)tex_pos;
		tex_y = clampi(tex_y, 0, tex->height - 1); /* clamp, don't wrap */
		*(unsigned int *)((*game)->addr + (long)y * (*game)->line_length + x * scr_bpp) = *(unsigned int *)(tex->addr + (long)tex_y * tex->sl + tex_x * tex->bytes_pp);
		tex_pos += step;
		y++;
	}
}
