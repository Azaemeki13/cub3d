/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:31:43 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 16:21:59 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mm_init(t_game *g, t_mm *m)
{
	int	size;

	size = 20;
	m->tile = MINIMAP_TILE_SIZE;
	m->clip.r = (size * m->tile) / 2;
	m->clip.cx = MINIMAP_OFFSET_X + m->clip.r;
	m->clip.cy = MINIMAP_OFFSET_Y + m->clip.r;
	m->start_x = (int)g->player->player_pos->x - size / 2;
	m->start_y = (int)g->player->player_pos->y - size / 2;
	m->end_x = m->start_x + size;
	m->end_y = m->start_y + size;
}

static int	mm_tile_color(t_game *g, int mx, int my)
{
	char	c;

	if (!mm_in_bounds(g, mx, my))
		return (create_rgb_color(64, 64, 64));
	c = g->map->map[my][mx];
	if (c == '1')
		return (create_rgb_color(0, 0, 0));
	if (c == 'D' || c == 'd')
		return (create_rgb_color(25, 210, 250));
	if (c == ' ')
		return (create_rgb_color(128, 128, 128));
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (create_rgb_color(200, 200, 200));
	return (create_rgb_color(128, 128, 128));
}

static void	mm_draw_tile(t_game *g, t_mm *m, int mx, int my)
{
	t_rect	r;
	int		sx;
	int		sy;
	int		color;

	sx = MINIMAP_OFFSET_X + (mx - m->start_x) * m->tile;
	sy = MINIMAP_OFFSET_Y + (my - m->start_y) * m->tile;
	color = mm_tile_color(g, mx, my);
	r.x = sx;
	r.y = sy;
	r.w = m->tile;
	r.h = m->tile;
	mm_fill_rect_clip(g, &r, &m->clip, color);
}

static void	mm_draw_player(t_game *g, t_mm *m)
{
	t_rect	r;

	r.x = m->clip.cx - m->tile / 2;
	r.y = m->clip.cy - m->tile / 2;
	r.w = m->tile;
	r.h = m->tile;
	mm_fill_rect_clip(g, &r, &m->clip, create_rgb_color(255, 0, 0));
}

void	draw_minimap(t_game *g)
{
	t_mm	m;
	int		my;
	int		mx;

	mm_init(g, &m);
	draw_circle_border(g, &m.clip, 2);
	my = m.start_y;
	while (my < m.end_y)
	{
		mx = m.start_x;
		while (mx < m.end_x)
		{
			mm_draw_tile(g, &m, mx, my);
			mx++;
		}
		my++;
	}
	mm_draw_player(g, &m);
}
