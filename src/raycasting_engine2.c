/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:16:12 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/26 16:16:27 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ray_casting_loop(t_raycaster *rc, t_game *game,
		int *wall_direction, double *wall_x)
{
	int		hit;
	double	door_dist;

	hit = 0;
	while (!hit)
	{
		if (dda_step(rc, game))
			break ;
		if (rc->tile == 'D')
		{
			door_dist = handle_door_collision(rc, game, wall_direction, wall_x);
			if (door_dist >= 0.0)
				return (door_dist);
		}
		else if (rc->tile == '1')
		{
			hit = 1;
			game->hit_tile = '1';
		}
	}
	return (-1.0);
}

double	ray_casting(int x, int *wall_direction, t_game *game, double *wall_x)
{
	t_raycaster	rc;
	double		door_dist;

	init_ray(&rc, x, game->player);
	set_deltas(&rc);
	set_steps(&rc);
	door_dist = ray_casting_loop(&rc, game, wall_direction, wall_x);
	if (door_dist >= 0.0)
		return (door_dist);
	*wall_direction = get_wall_direction(rc.side, rc.step_x, rc.step_y);
	compute_perp_dist(&rc);
	if (rc.side == 0)
		*wall_x = rc.py + rc.perp_wall_dist * rc.ray.ray_dir.y;
	else
		*wall_x = rc.px + rc.perp_wall_dist * rc.ray.ray_dir.x;
	*wall_x -= floor(*wall_x);
	game->side_out = rc.side;
	game->ray_dir.x = rc.ray.ray_dir.x;
	game->ray_dir.y = rc.ray.ray_dir.y;
	return (rc.perp_wall_dist);
}
