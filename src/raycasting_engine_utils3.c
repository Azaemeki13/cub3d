/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine_utils3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:19:56 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/25 17:23:11 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	compute_perp_dist(t_raycaster *rc)
{
	if (rc->side == 0)
		rc->perp_wall_dist = ((double)rc->map_x - rc->px + (1.0
					- (double)rc->step_x) / 2.0) / rc->ray.ray_dir.x;
	else
		rc->perp_wall_dist = ((double)rc->map_y - rc->py + (1.0
					- (double)rc->step_y) / 2.0) / rc->ray.ray_dir.y;
	return (rc->perp_wall_dist);
}

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
	range.height = (int)(WIN_HEIGHT / perp_wall_dist);
	range.start = (WIN_HEIGHT - range.height) / 2 + game->player->pitch;
	range.end = (WIN_HEIGHT + range.height) / 2 + game->player->pitch;
	return (range);
}

static void	draw_pixel(t_game *game_data, int x, int y, int color)
{
	char	*dst;

	dst = game_data->addr + (y * game_data->line_length + x
			* (game_data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_vertical_line(t_game *game_data, int x, int start, int end)
{
	int	y;

	if (start < 0)
		start = 0;
	if (end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;
	if (start > end)
		return ;
	y = start;
	while (y <= end)
	{
		draw_pixel(game_data, x, y, game_data->current_color);
		y++;
	}
}
