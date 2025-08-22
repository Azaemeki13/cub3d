/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:49:18 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 15:27:41 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_toggle_at(t_game *game, int x, int y)
{
	t_door	*door;
	int		px;
	int		py;

	door = door_at(game, x, y);
	if (!door)
		return ;
	px = (int)game->player->player_pos->x;
	py = (int)game->player->player_pos->y;
	if (door->target && door->frac > 0.5)
	{
		if (!(px == x && py == y))
			door->target = 0;
	}
	else
		door->target = 1;
}

void	doors_update(t_game *game, double dt)
{
	int		i;
	int		n;
	double	step;
	t_door	*door;

	n = game->map->map_width * game->map->map_height;
	if (dt > 0.0)
		step = game->door_speed * dt;
	else
		step = 0.03;
	i = 0;
	while (i < n)
	{
		door = &game->doors[i++];
		if (!door->active)
			continue ;
		if (door->target && door->frac < 1.0)
		{
			door->frac += step;
			if (door->frac > 1.0)
				door->frac = 1.0;
		}
		else if (!door->target && door->frac > 0.0)
		{
			door->frac -= step;
			if (door->frac < 0.0)
				door->frac = 0.0;
		}
	}
}
