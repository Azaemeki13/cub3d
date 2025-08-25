/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_door_handling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:48:42 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/25 16:58:45 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_wall_sign(t_game *game, int map_x, int map_y, int side)
{
	if (side == 0)
	{
		if (map_y + 1 < game->map->map_height && game->map->map[map_y
				+ 1][map_x] == '1')
			return (1);
		else if (map_y - 1 >= 0 && game->map->map[map_y - 1][map_x] == '1')
			return (-1);
	}
	else
	{
		if (map_x + 1 < game->map->map_width && game->map->map[map_y][map_x
			+ 1] == '1')
			return (1);
		else if (map_x - 1 >= 0 && game->map->map[map_y][map_x - 1] == '1')
			return (-1);
	}
	return (0);
}

void	set_collision_result(t_game *game, t_raycaster *rc, int *wall_direction)
{
	*wall_direction = get_wall_direction(rc->side, rc->step_x, rc->step_y);
	game->side_out = rc->side;
	game->ray_dir.x = rc->ray.ray_dir.x;
	game->ray_dir.y = rc->ray.ray_dir.y;
	game->hit_tile = 'D';
}

double	handle_vertical_door(t_raycaster *rc, t_game *game, int *wall_direction,
		double *wall_x)
{
	double	f;
	double	xentry;
	double	tdoor;
	int		sign;
	double	y_hit;
	double	door_y0;

	f = door_at(game, rc->map_x, rc->map_y)->frac;
	sign = get_wall_sign(game, rc->map_x, rc->map_y, 0);
	if (rc->step_x > 0)
		xentry = (double)rc->map_x;
	else
		xentry = (double)rc->map_x + 1.0;
	tdoor = (xentry - rc->px) / rc->ray.ray_dir.x;
	if (sign == 0)
	{
		tdoor = (xentry + f * (double)rc->step_x - rc->px) / rc->ray.ray_dir.x;
		if (tdoor > 0.0 && tdoor <= rc->side_dist_y)
		{
			*wall_x = rc->py + tdoor * rc->ray.ray_dir.y;
			*wall_x -= floor(*wall_x);
			set_collision_result(game, rc, wall_direction);
			return (tdoor);
		}
	}
	else
	{
		y_hit = rc->py + tdoor * rc->ray.ray_dir.y;
		door_y0 = (double)rc->map_y;
		if (sign > 0)
			door_y0 = (double)rc->map_y + f;
		else if (sign < 0)
			door_y0 = (double)rc->map_y - f;
		if (tdoor > 0.0 && tdoor <= rc->side_dist_y && y_hit >= door_y0
			&& y_hit < door_y0 + 1.0)
		{
			*wall_x = y_hit - door_y0;
			set_collision_result(game, rc, wall_direction);
			return (tdoor);
		}
	}
	return (-1);
}

double	handle_horizontal_door(t_raycaster *rc, t_game *game,
		int *wall_direction, double *wall_x)
{
	double	f;
	double	yentry;
	double	tdoor;
	int		sign;
	double	x_hit;
	double	door_x0;

	f = door_at(game, rc->map_x, rc->map_y)->frac;
	sign = get_wall_sign(game, rc->map_x, rc->map_y, 1);
	if (rc->step_y > 0)
		yentry = (double)rc->map_y;
	else
		yentry = (double)rc->map_y + 1.0;
	tdoor = (yentry - rc->py) / rc->ray.ray_dir.y;
	if (sign == 0)
	{
		tdoor = (yentry + f * (double)rc->step_y - rc->py) / rc->ray.ray_dir.y;
		if (tdoor > 0.0 && tdoor <= rc->side_dist_x)
		{
			*wall_x = rc->px + tdoor * rc->ray.ray_dir.x;
			*wall_x -= floor(*wall_x);
			set_collision_result(game, rc, wall_direction);
			return (tdoor);
		}
	}
	else
	{
		x_hit = rc->px + tdoor * rc->ray.ray_dir.x;
		door_x0 = (double)rc->map_x;
		if (sign > 0)
			door_x0 = (double)rc->map_x + f;
		else if (sign < 0)
			door_x0 = (double)rc->map_x - f;
		if (tdoor > 0.0 && tdoor <= rc->side_dist_x && x_hit >= door_x0
			&& x_hit < door_x0 + 1.0)
		{
			*wall_x = x_hit - door_x0;
			set_collision_result(game, rc, wall_direction);
			return (tdoor);
		}
	}
	return (-1);
}

double	handle_door_collision(t_raycaster *rc, t_game *game,
		int *wall_direction, double *wall_x)
{
	t_door	*door;
	double	f;

	door = door_at(game, rc->map_x, rc->map_y);
	f = 0.0;
	if (door)
		f = door->frac;
	if (f >= 0.99)
		return (-1);
	if (rc->side == 0)
		return (handle_vertical_door(rc, game, wall_direction, wall_x));
	else
		return (handle_horizontal_door(rc, game, wall_direction, wall_x));
}
