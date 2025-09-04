/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_door_handling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:48:42 by chsauvag          #+#    #+#             */
/*   Updated: 2025/09/04 09:44:54 by cauffret         ###   ########.fr       */
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
	t_vert_door	vd;
	double		t;

	vd.f = door_at(game, rc->map_x, rc->map_y)->frac;
	vd.sign = get_wall_sign(game, rc->map_x, rc->map_y, 0);
	if (rc->step_x > 0)
		vd.xentry = (double)rc->map_x;
	else
		vd.xentry = (double)rc->map_x + 1.0;
	vd.tdoor = (vd.xentry - rc->px) / rc->ray.ray_dir.x;
	if (vd.sign == 0)
		t = vert_door_closed(&vd, rc, game);
	else
		t = vert_door_open(&vd, rc, game);
	if (t > 0.0)
	{
		*wall_x = vd.wall_x;
		*wall_direction = vd.wall_direction;
		return (t);
	}
	return (-1);
}

double	handle_horizontal_door(t_raycaster *rc, t_game *game,
		int *wall_direction, double *wall_x)
{
	t_horiz_door	hd;
	double			t;

	hd.f = door_at(game, rc->map_x, rc->map_y)->frac;
	hd.sign = get_wall_sign(game, rc->map_x, rc->map_y, 1);
	if (rc->step_y > 0)
		hd.yentry = (double)rc->map_y;
	else
		hd.yentry = (double)rc->map_y + 1.0;
	hd.tdoor = (hd.yentry - rc->py) / rc->ray.ray_dir.y;
	if (hd.sign == 0)
		t = horiz_door_closed(&hd, rc, game);
	else
		t = horiz_door_open(&hd, rc, game);
	if (t > 0.0)
	{
		*wall_x = hd.wall_x;
		*wall_direction = hd.wall_direction;
		return (t);
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
