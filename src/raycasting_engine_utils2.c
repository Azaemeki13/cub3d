/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_engine_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:24:04 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 16:35:40 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	clip_span(t_game *g, t_texspan *s)
{
	if (s->end < 0 || s->start >= WIN_HEIGHT)
		return (0);
	if (g->range.height <= 0)
		return (0);
	if (s->start < 0)
		s->start = 0;
	if (s->end >= WIN_HEIGHT)
		s->end = WIN_HEIGHT - 1;
	return (1);
}

static double	tex_start_u(t_game *g)
{
	return (-g->range.height / 2.0 + WIN_HEIGHT / 2.0 + g->player->pitch);
}

static void	draw_span_loop(t_game *g, t_texspan *s)
{
	int		y;
	int		tex_y;
	double	tex_pos;

	tex_pos = (s->start - tex_start_u(g)) * s->step;
	y = s->start;
	while (y <= s->end)
	{
		tex_y = (int)tex_pos;
		tex_y = clampi(tex_y, 0, s->tex->height - 1);
		*(unsigned int *)(g->addr + (long)y * g->line_length
			+ s->x * (g->bits_per_pixel / 8)) =
		*(unsigned int *)(s->tex->addr + (long)tex_y * s->tex->sl
			+ s->tex_x * s->tex->bytes_pp);
		tex_pos += s->step;
		y++;
	}
}

static void	draw_tex_column(t_game *g, t_texspan *s)
{
	if (!clip_span(g, s))
		return ;
	s->tex_x = compute_tex_x(g, s->tex);
	s->step = (double)s->tex->height / (double)g->range.height;
	draw_span_loop(g, s);
}

void	draw_textures(t_game **game, int x, int start, int end, t_text *tex)
{
	t_texspan	s;

	s.x = x;
	s.start = start;
	s.end = end;
	s.tex = tex;
	draw_tex_column(*game, &s);
}

