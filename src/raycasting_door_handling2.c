/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_door_handling2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:27:45 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/26 14:42:55 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	vert_door_closed(t_vert_door *vd, t_raycaster *rc, t_game *game)
{
	vd->tdoor = (vd->xentry + vd->f * (double)rc->step_x - rc->px)
		/ rc->ray.ray_dir.x;
	if (vd->tdoor > 0.0 && vd->tdoor <= rc->side_dist_y)
	{
		vd->wall_x = rc->py + vd->tdoor * rc->ray.ray_dir.y;
		vd->wall_x -= floor(vd->wall_x);
		set_collision_result(game, rc, &vd->wall_direction);
		return (vd->tdoor);
	}
	return (-1);
}

double	vert_door_open(t_vert_door *vd, t_raycaster *rc, t_game *game)
{
	vd->y_hit = rc->py + vd->tdoor * rc->ray.ray_dir.y;
	vd->door_y0 = (double)rc->map_y;
	if (vd->sign > 0)
		vd->door_y0 = (double)rc->map_y + vd->f;
	else if (vd->sign < 0)
		vd->door_y0 = (double)rc->map_y - vd->f;
	if (vd->tdoor > 0.0 && vd->tdoor <= rc->side_dist_y
		&& vd->y_hit >= vd->door_y0 && vd->y_hit < vd->door_y0 + 1.0)
	{
		vd->wall_x = vd->y_hit - vd->door_y0;
		set_collision_result(game, rc, &vd->wall_direction);
		return (vd->tdoor);
	}
	return (-1);
}

double	horiz_door_closed(t_horiz_door *hd, t_raycaster *rc, t_game *game)
{
	hd->tdoor = (hd->yentry + hd->f * (double)rc->step_y - rc->py)
		/ rc->ray.ray_dir.y;
	if (hd->tdoor > 0.0 && hd->tdoor <= rc->side_dist_x)
	{
		hd->wall_x = rc->px + hd->tdoor * rc->ray.ray_dir.x;
		hd->wall_x -= floor(hd->wall_x);
		set_collision_result(game, rc, &hd->wall_direction);
		return (hd->tdoor);
	}
	return (-1);
}

double	horiz_door_open(t_horiz_door *hd, t_raycaster *rc, t_game *game)
{
	hd->x_hit = rc->px + hd->tdoor * rc->ray.ray_dir.x;
	hd->door_x0 = (double)rc->map_x;
	if (hd->sign > 0)
		hd->door_x0 = (double)rc->map_x + hd->f;
	else if (hd->sign < 0)
		hd->door_x0 = (double)rc->map_x - hd->f;
	if (hd->tdoor > 0.0 && hd->tdoor <= rc->side_dist_x
		&& hd->x_hit >= hd->door_x0 && hd->x_hit < hd->door_x0 + 1.0)
	{
		hd->wall_x = hd->x_hit - hd->door_x0;
		set_collision_result(game, rc, &hd->wall_direction);
		return (hd->tdoor);
	}
	return (-1);
}
