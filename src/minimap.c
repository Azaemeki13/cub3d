/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:27:58 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/22 16:07:17 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	inside_circle(int x, int y, t_circle *c)
{
	int	dx;
	int	dy;

	dx = x - c->cx;
	dy = y - c->cy;
	return (dx * dx + dy * dy <= c->r * c->r);
}

static void	mm_putpx(t_game *g, t_px *p)
{
	char	*dst;

	if (p->x < 0 || p->x >= WIN_WIDTH || p->y < 0 || p->y >= WIN_HEIGHT)
		return ;
	dst = g->addr + (p->y * g->line_length + p->x * (g->bits_per_pixel / 8));
	*(unsigned int *)dst = p->color;
}

static void	mm_putpx_clip(t_game *g, t_px *p, t_circle *clip)
{
	if (p->x < 0 || p->x >= WIN_WIDTH || p->y < 0 || p->y >= WIN_HEIGHT)
		return ;
	if (!inside_circle(p->x, p->y, clip))
		return ;
	mm_putpx(g, p);
}

void	mm_fill_rect_clip(t_game *g, t_rect *r, t_circle *clip, int color)
{
	int		x;
	int		y;
	t_px	p;

	y = r->y;
	while (y < r->y + r->h)
	{
		x = r->x;
		while (x < r->x + r->w)
		{
			p.x = x;
			p.y = y;
			p.color = color;
			mm_putpx_clip(g, &p, clip);
			x++;
		}
		y++;
	}
}

void	draw_circle_border(t_game *g, t_circle *c, int thickness)
{
	int	x;
	int	y;
	int	d2;

	y = c->cy - c->r - thickness;
	while (y <= c->cy + c->r + thickness)
	{
		x = c->cx - c->r - thickness;
		while (x <= c->cx + c->r + thickness)
		{
			d2 = (x - c->cx) * (x - c->cx) + (y - c->cy) * (y - c->cy);
			if (d2 <= (c->r + thickness) * (c->r + thickness)
				&& d2 > c->r * c->r)
				mm_putpx_clip(g,
					&(t_px){x, y, create_rgb_color(255, 255, 255)},
					&(t_circle){c->cx, c->cy, c->r + thickness});
			x++;
		}
		y++;
	}
}
