/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:33:19 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 15:24:19 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_setup_dirs(t_game *g, t_dda *s)
{
	s->px = g->player->player_pos->x;
	s->py = g->player->player_pos->y;
	s->map_x = (int)s->px;
	s->map_y = (int)s->py;
	s->ray.ray_dir.x = g->player->vector_dir->x;
	s->ray.ray_dir.y = g->player->vector_dir->y;
	if (s->ray.ray_dir.x == 0)
		s->delta_x = 1e30;
	else
		s->delta_x = fabs(1.0 / s->ray.ray_dir.x);
	if (s->ray.ray_dir.y == 0)
		s->delta_y = 1e30;
	else
		s->delta_y = fabs(1.0 / s->ray.ray_dir.y);
}

void	dda_setup_steps(t_dda *s)
{
	if (s->ray.ray_dir.x < 0)
	{
		s->step_x = -1;
		s->side_dist_x = (s->px - s->map_x) * s->delta_x;
	}
	else
	{
		s->step_x = 1;
		s->side_dist_x = (s->map_x + 1.0 - s->px) * s->delta_x;
	}
	if (s->ray.ray_dir.y < 0)
	{
		s->step_y = -1;
		s->side_dist_y = (s->py - s->map_y) * s->delta_y;
	}
	else
	{
		s->step_y = 1;
		s->side_dist_y = (s->map_y + 1.0 - s->py) * s->delta_y;
	}
}

int	dda_oob(t_game *g, t_dda *s)
{
	if (s->map_x < 0 || s->map_x >= g->map->map_width)
		return (1);
	if (s->map_y < 0 || s->map_y >= g->map->map_height)
		return (1);
	return (0);
}

int	interact_cast(t_game *g)
{
	t_dda	s;
	char	tile;

	dda_setup_dirs(g, &s);
	dda_setup_steps(&s);
	if (dda_step_and_hit(g, &s) != 1)
		return (0);
	if (!dda_compute_t(&s))
		return (0);
	tile = g->map->map[s.map_y][s.map_x];
	if (tile == 'D' || tile == 'd')
	{
		set_vector(&g->map->door_pos, (double)s.map_x, (double)s.map_y);
		return (1);
	}
	return (0);
}

void	door_use(t_game *game)
{
	int	x;
	int	y;

	if (interact_cast(game))
	{
		x = (int)game->map->door_pos.x;
		y = (int)game->map->door_pos.y;
		door_toggle_at(game, x, y);
	}
}
