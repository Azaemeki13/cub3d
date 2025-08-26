/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reticle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:18:51 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/26 16:15:31 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_reticle_top(t_reticle *r)
{
	int	x;
	int	y;

	y = r->cy - r->size;
	while (y <= (r->cy - r->gap - 1))
	{
		x = r->x_start;
		while (x <= r->x_end)
		{
			draw_minimap_pixel(r->game, x, y, create_rgb_color(255, 0, 0));
			x++;
		}
		y++;
	}
}

static void	draw_reticle_middle(t_reticle *r)
{
	int	x;
	int	y;

	y = r->y_start;
	while (y <= r->y_end)
	{
		x = r->cx - r->size;
		while (x <= r->cx - r->gap - 1)
			draw_minimap_pixel(r->game, x++, y, create_rgb_color(255, 0, 0));
		x = r->cx + r->gap + 1;
		while (x <= (r->cx + r->size))
			draw_minimap_pixel(r->game, x++, y, create_rgb_color(255, 0, 0));
		y++;
	}
}

static void	draw_reticle_bottom(t_reticle *r)
{
	int	x;
	int	y;

	y = r->cy + r->gap + 1;
	while (y <= (r->cy + r->size))
	{
		x = r->x_start;
		while (x <= r->x_end)
		{
			draw_minimap_pixel(r->game, x, y, create_rgb_color(255, 0, 0));
			x++;
		}
		y++;
	}
}

void	draw_reticle(t_game **game, int thick, int size)
{
	t_reticle	r;

	if (size <= 3)
		return ;
	r.game = *game;
	r.thick = thick;
	r.size = size;
	r.gap = 3;
	r.cx = WIN_WIDTH / 2;
	r.cy = WIN_HEIGHT / 2;
	r.x_start = r.cx - (thick / 2);
	r.x_end = r.cx + (thick - 1) / 2;
	r.y_start = r.cy - (thick / 2);
	r.y_end = r.cy + (thick - 1) / 2;
	draw_reticle_top(&r);
	draw_reticle_middle(&r);
	draw_reticle_bottom(&r);
}
