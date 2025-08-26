/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:15:42 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/26 16:19:12 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_raycaster *rc, int x, t_player *player)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (double)WIN_WIDTH - 1.0;
	rc->ray.ray_dir.x = player->vector_dir->x + player->camera_plane->x
		* camera_x;
	rc->ray.ray_dir.y = player->vector_dir->y + player->camera_plane->y
		* camera_x;
	rc->map_x = (int)player->player_pos->x;
	rc->map_y = (int)player->player_pos->y;
	rc->px = player->player_pos->x;
	rc->py = player->player_pos->y;
}

void	set_deltas(t_raycaster *rc)
{
	if (rc->ray.ray_dir.x == 0.0)
		rc->delta_x = 1e30;
	else
		rc->delta_x = fabs(1.0 / rc->ray.ray_dir.x);
	if (rc->ray.ray_dir.y == 0.0)
		rc->delta_y = 1e30;
	else
		rc->delta_y = fabs(1.0 / rc->ray.ray_dir.y);
}

void	set_steps(t_raycaster *rc)
{
	if (rc->ray.ray_dir.x < 0.0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->px - (double)rc->map_x) * rc->delta_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = ((double)rc->map_x + 1.0 - rc->px) * rc->delta_x;
	}
	if (rc->ray.ray_dir.y < 0.0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->py - (double)rc->map_y) * rc->delta_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = ((double)rc->map_y + 1.0 - rc->py) * rc->delta_y;
	}
}

int	dda_step(t_raycaster *rc, t_game *game)
{
	if (rc->side_dist_x < rc->side_dist_y)
	{
		rc->side_dist_x += rc->delta_x;
		rc->map_x += rc->step_x;
		rc->side = 0;
	}
	else
	{
		rc->side_dist_y += rc->delta_y;
		rc->map_y += rc->step_y;
		rc->side = 1;
	}
	if (rc->map_x < 0 || rc->map_x >= game->map->map_width || rc->map_y < 0
		|| rc->map_y >= game->map->map_height)
	{
		game->hit_tile = '1';
		return (1);
	}
	rc->tile = game->map->map[rc->map_y][rc->map_x];
	return (0);
}
