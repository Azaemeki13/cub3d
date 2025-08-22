/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_dda2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:19:08 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 16:45:59 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dda_step_and_hit(t_game *g, t_dda *s)
{
	int		hit;
	char	c;

	hit = 0;
	while (hit == 0)
	{
		if (s->side_dist_x < s->side_dist_y)
		{
			s->side_dist_x += s->delta_x;
			s->map_x += s->step_x;
			s->side = 0;
		}
		else
		{
			s->side_dist_y += s->delta_y;
			s->map_y += s->step_y;
			s->side = 1;
		}
		if (dda_oob(g, s))
			return (-1);
		c = g->map->map[s->map_y][s->map_x];
		if (c == 'D' || c == 'd' || c == '1')
			hit = 1;
	}
	return (1);
}

int	dda_compute_t(t_dda *s)
{
	if (s->side == 0)
		s->t = (s->map_x - s->px + (1.0 - s->step_x) / 2.0) / s->ray.ray_dir.x;
	else
		s->t = (s->map_y - s->py + (1.0 - s->step_y) / 2.0) / s->ray.ray_dir.y;
	if (s->t > USE_RANGE || s->t < 0)
		return (0);
	return (1);
}
