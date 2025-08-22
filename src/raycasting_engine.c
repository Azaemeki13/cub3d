/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:15:42 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/19 17:47:27 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*double ray_casting(int x, t_player player)
{
	double	camera_x;
	int		wall_hit;
		t_ray ray;
		t_vector side_dist;
	int		hit;
	int		side;
	double	perp_wall_dist;
	double	camera_x;
	t_ray	ray;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit;
	int		side;
	double	hit_x;
	double	hit_y;
	double	perp_wall_dist;
	t_door	*door;
	char	tile;
	double	f;
	double	tdoor;
	double	xentry;
	double	yentry;
	double	px;
	double	py;
	int		sign;
	double	door_y0;
	double	door_x0;
	double	y_hit;
	double	x_hit;

	wall_hit = 0;
	while(x < WIN_WIDTH)
	{
		///////////////////// RAY DIRECTION CALCULATIONS ///////////////////////
		camera_x = 2 * x / (double)WIN_WIDTH - 1; // that's 2 * 0 / 1024 - 1 =
			-1.0 (far left) if camera_x = 0
		ray->ray_dir.x = player.dir.x + player.plane.x * camera_x;
			// ray direction in x ray_dir = center_direction + spread_left_right
		ray->ray_dir.y = player.dir.y + player.plane.y * camera_x;
		ray.map.x = (int)player.pos.x;
			//takes the current floating point and converts
		ray.map.y = (int)player.pos.y;
			//it to an integer to indicate the current tile the character is standing on
		delta.x = fabs(1 / ray->ray_dir.x);
			//delta x is the distance to the next vertical line
		delta.y = fabs(1 / ray->ray_dir.y);
			//delta y is the distance to the next horizontal line
		/////////////////// STEP DIRECTIONS CALCULATIONS //////////////////////
		if(ray.ray_dir.x < 0) //left
		{
			step_dir_x = -1; //if ray direction is negative, we step left
			side_dist.x = (player.pos.x - ray.map.x) * delta.x;
			//side is the distance to hit the edge of the current tile to the left
		}
		else if (ray.ray_dir.x > 0) //right
		{
			step_dir_x = 1;
			side_dist.x = (ray.map.x + 1.0 - player.pos.x) * delta.x;
		}
		if(ray.ray_dir.y < 0) //up
		{
			step_dir_y = -1;
			side_dist.y = (player.pos.y - ray.map.y) * delta.y;
		}
		else if (ray.ray_dir.y > 0) //down
		{
			step_dir_y = 1;
			side_dist.y = (ray.map.y + 1.0 - player.pos.y) * delta.y;
		}
		/////////////////// DDA LOOP //////////////////////
	hit = 0;
	side = 0;
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_y;
			map_y += step_y;
			side = 1;
		}
		if (world_map[map_x][map_y] > 0)
			hit = 1;
	}
	if (side == 0)
		perp_wall_dist = (map_x - player.pos.x + (1 - step_x) / 2)
			/ ray.ray_dir.x;
	else
		perp_wall_dist = (map_y - player.pos.y + (1 - step_y) / 2)
			/ ray.ray_dir.y;
	printf("Column %d hit wall at distance: %f\n", x, perp_wall_dist);
	return (perp_wall_dist);
}*/
double	ray_casting(int x, t_player *player, int *wall_direction, t_game *game,
		double *wall_x)
{
	camera_x = 2.0 * (double)x / (double)WIN_WIDTH - 1.0;
	ray.ray_dir.x = player->vector_dir->x + player->camera_plane->x * camera_x;
	ray.ray_dir.y = player->vector_dir->y + player->camera_plane->y * camera_x;
	map_x = (int)player->player_pos->x;
	map_y = (int)player->player_pos->y;
	px = player->player_pos->x;
	py = player->player_pos->y;
	if (ray.ray_dir.x == 0.0)
		delta_x = 1e30;
	else
		delta_x = fabs(1.0 / ray.ray_dir.x);
	if (ray.ray_dir.y == 0.0)
		delta_y = 1e30;
	else
		delta_y = fabs(1.0 / ray.ray_dir.y);
	if (ray.ray_dir.x < 0.0)
	{
		step_x = -1;
		side_dist_x = (px - (double)map_x) * delta_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = ((double)map_x + 1.0 - px) * delta_x;
	}
	if (ray.ray_dir.y < 0.0)
	{
		step_y = -1;
		side_dist_y = (py - (double)map_y) * delta_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = ((double)map_y + 1.0 - py) * delta_y;
	}
	hit = 0;
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_y;
			map_y += step_y;
			side = 1;
		}
		if (map_x < 0 || map_x >= game->map->map_width || map_y < 0
			|| map_y >= game->map->map_height)
		{
			hit = 1;
			game->hit_tile = '1';
			break ;
		}
		tile = game->map->map[map_y][map_x];
		if (tile == 'D')
		{
			door = door_at(game, map_x, map_y);
			f = 0.0;
			if (door)
				f = door->frac;
			if (f >= 0.99)
				continue ;
			if (side == 0)
			{
				if (step_x > 0)
					xentry = (double)map_x;
				else
					xentry = (double)map_x + 1.0;
				tdoor = (xentry - px) / ray.ray_dir.x;
				sign = 0;
				if (map_y + 1 < game->map->map_height && game->map->map[map_y
					+ 1][map_x] == '1')
					sign = 1;
				else if (map_y - 1 >= 0 && game->map->map[map_y
					- 1][map_x] == '1')
					sign = -1;
				if (sign == 0)
				{
					if (step_x > 0)
						xentry = (double)map_x;
					else
						xentry = (double)map_x + 1.0;
					tdoor = (xentry + f * (double)step_x - px) / ray.ray_dir.x;
					if (tdoor > 0.0 && tdoor <= side_dist_y)
					{
						*wall_direction = get_wall_direction(side, step_x,
								step_y);
						*wall_x = py + tdoor * ray.ray_dir.y;
						*wall_x -= floor(*wall_x);
						game->side_out = 0;
						game->ray_dir.x = ray.ray_dir.x;
						game->ray_dir.y = ray.ray_dir.y;
						game->hit_tile = 'D';
						return (tdoor);
					}
				}
				else
				{
					y_hit = py + tdoor * ray.ray_dir.y;
					door_y0 = (double)map_y;
					if (sign > 0)
						door_y0 = (double)map_y + f;
					else if (sign < 0)
						door_y0 = (double)map_y - f;
					if (tdoor > 0.0 && tdoor <= side_dist_y && y_hit >= door_y0
						&& y_hit < door_y0 + 1.0)
					{
						*wall_direction = get_wall_direction(side, step_x,
								step_y);
						*wall_x = y_hit - door_y0;
						game->side_out = 0;
						game->ray_dir.x = ray.ray_dir.x;
						game->ray_dir.y = ray.ray_dir.y;
						game->hit_tile = 'D';
						return (tdoor);
					}
				}
			}
			else
			{
				if (step_y > 0)
					yentry = (double)map_y;
				else
					yentry = (double)map_y + 1.0;
				tdoor = (yentry - py) / ray.ray_dir.y;
				sign = 0;
				if (map_x + 1 < game->map->map_width
					&& game->map->map[map_y][map_x + 1] == '1')
					sign = 1;
				else if (map_x - 1 >= 0 && game->map->map[map_y][map_x
					- 1] == '1')
					sign = -1;
				if (sign == 0)
				{
					if (step_y > 0)
						yentry = (double)map_y;
					else
						yentry = (double)map_y + 1.0;
					tdoor = (yentry + f * (double)step_y - py) / ray.ray_dir.y;
					if (tdoor > 0.0 && tdoor <= side_dist_x)
					{
						*wall_direction = get_wall_direction(side, step_x,
								step_y);
						*wall_x = px + tdoor * ray.ray_dir.x;
						*wall_x -= floor(*wall_x);
						game->side_out = 1;
						game->ray_dir.x = ray.ray_dir.x;
						game->ray_dir.y = ray.ray_dir.y;
						game->hit_tile = 'D';
						return (tdoor);
					}
				}
				else
				{
					x_hit = px + tdoor * ray.ray_dir.x;
					door_x0 = (double)map_x;
					if (sign > 0)
						door_x0 = (double)map_x + f;
					else if (sign < 0)
						door_x0 = (double)map_x - f;
					if (tdoor > 0.0 && tdoor <= side_dist_x && x_hit >= door_x0
						&& x_hit < door_x0 + 1.0)
					{
						*wall_direction = get_wall_direction(side, step_x,
								step_y);
						*wall_x = x_hit - door_x0;
						game->side_out = 1;
						game->ray_dir.x = ray.ray_dir.x;
						game->ray_dir.y = ray.ray_dir.y;
						game->hit_tile = 'D';
						return (tdoor);
					}
				}
			}
		}
		else if (tile == '1')
		{
			hit = 1;
			game->hit_tile = '1';
		}
	}
	*wall_direction = get_wall_direction(side, step_x, step_y);
	if (side == 0)
		perp_wall_dist = ((double)map_x - px + (1.0 - (double)step_x) / 2.0)
			/ ray.ray_dir.x;
	else
		perp_wall_dist = ((double)map_y - py + (1.0 - (double)step_y) / 2.0)
			/ ray.ray_dir.y;
	hit_x = px + perp_wall_dist * ray.ray_dir.x;
	hit_y = py + perp_wall_dist * ray.ray_dir.y;
	if (side == 0)
		*wall_x = hit_y;
	else
		*wall_x = hit_x;
	*wall_x = *wall_x - floor(*wall_x);
	game->side_out = side;
	game->ray_dir.x = ray.ray_dir.x;
	game->ray_dir.y = ray.ray_dir.y;
	return (perp_wall_dist);
}

// wall height : line_height = (int)(WIN_HEIGHT / perp_wall_dist);

t_drawrange	calculate_draw_range(double perp_wall_dist, t_game *game)
{
	t_drawrange	range;

	if (perp_wall_dist <= 0)
	{
		range.start = 0;
		range.end = WIN_HEIGHT - 1;
		range.height = WIN_HEIGHT;
		return (range);
	}
	// calculate the height of the wall line
	range.height = (int)(WIN_HEIGHT / perp_wall_dist);
	// calculate the start and end of the wall line
	range.start = (WIN_HEIGHT - range.height) / 2 + game->player->pitch;
	range.end = (WIN_HEIGHT + range.height) / 2 + game->player->pitch;
	return (range);
}

void	draw_vertical_line(t_game *game_data, int x, int start, int end,
		int color)
{
	int y;
	char *dst;

	if (start < 0)
		start = 0;
	if (end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;
	if (start > end)
		return ;

	y = start;
	while (y <= end)
	{
		dst = game_data->addr + (y * game_data->line_length + x
				* (game_data->bits_per_pixel / 8));
		// frame buffer address calculation for rendering
		*(unsigned int *)dst = color;
		// set pixel color
		y++;
	}
}