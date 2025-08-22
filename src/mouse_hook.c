/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:36:27 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 16:20:46 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	iabs(int v)
{
	if (v < 0)
		return (-v);
	return (v);
}

static void	yaw_rotate(t_player *p, double angle)
{
	double	old_x;
	double	old_px;

	old_x = p->vector_dir->x;
	p->vector_dir->x = p->vector_dir->x * cos(angle)
		- p->vector_dir->y * sin(angle);
	p->vector_dir->y = old_x * sin(angle)
		+ p->vector_dir->y * cos(angle);
	old_px = p->camera_plane->x;
	p->camera_plane->x = p->camera_plane->x * cos(angle)
		- p->camera_plane->y * sin(angle);
	p->camera_plane->y = old_px * sin(angle)
		+ p->camera_plane->y * cos(angle);
}

static void	pitch_move(t_game *g, int dy)
{
	double	delta;
	int		limit;

	delta = -dy * g->mouse_sens * 300.0;
	g->player->pitch += delta;
	limit = WIN_HEIGHT / 3;
	if (g->player->pitch > limit)
		g->player->pitch = limit;
	if (g->player->pitch < -limit)
		g->player->pitch = -limit;
}

static void	recenter_mouse(t_game *g)
{
	mlx_mouse_move(g->mlx, g->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

int	on_mouse_move(int x, int y, void *param)
{
	t_game	*game;
	int		dx;
	int		dy;

	game = (t_game *)param;
	if (game->game_pause)
	{
		game->last_mouse_x = x;
		return (0);
	}
	dx = x - (WIN_WIDTH / 2);
	dy = y - (WIN_HEIGHT / 2);
	if (iabs(dx) < 2 && iabs(dy) < 2)
	{
		recenter_mouse(game);
		return (0);
	}
	if (iabs(dx) >= 2)
		yaw_rotate(game->player, dx * game->mouse_sens);
	if (iabs(dy) >= 2)
		pitch_move(game, dy);
	recenter_mouse(game);
	return (0);
}
