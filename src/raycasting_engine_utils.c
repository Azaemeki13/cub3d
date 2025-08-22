/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:51:29 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 16:33:54 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_pow2(int n)
{
	return (n > 0 && (n & (n - 1)) == 0);
}

void	set_bytespp(t_game **game)
{
	t_map	*map;

	map = (*game)->map;
	map->no->bytes_pp = map->no->bpp / 8;
	map->ea->bytes_pp = map->ea->bpp / 8;
	map->so->bytes_pp = map->so->bpp / 8;
	map->we->bytes_pp = map->we->bpp / 8;
	map->door->bytes_pp = map->door->bpp / 8;
}

int	clampi(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

int	compute_tex_x(t_game *g, t_text *tex)
{
	int	tx;

	tx = (int)(g->wall_x * (double)tex->width);
	if (g->side_out == 0 && g->ray_dir.x > 0)
		tx = tex->width - tx - 1;
	else if (g->side_out == 1 && g->ray_dir.y < 0)
		tx = tex->width - tx - 1;
	return (clampi(tx, 0, tex->width - 1));
}

t_text	*get_wall_text(int wall_dir, t_game **game)
{
	t_map	*map;

	map = (*game)->map;
	if ((*game)->hit_tile == '1')
	{
		if (wall_dir == NORTH)
			return (map->no);
		else if (wall_dir == EAST)
			return (map->ea);
		else if (wall_dir == SOUTH)
			return (map->so);
		else if (wall_dir == WEST)
			return (map->we);
	}
	else if ((*game)->hit_tile == 'D' && map->door)
		return (map->door);
	return (map->no);
}
