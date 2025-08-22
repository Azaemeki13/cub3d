/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:16:22 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 16:46:32 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	start_helper(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

void	set_vector(t_vector *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
}

void	init_orientation(t_game **game)
{
	char		orientation;
	t_vector	*vector;
	t_vector	*plane;

	vector = (*game)->player->vector_dir;
	plane = (*game)->player->camera_plane;
	orientation = (*game)->player->orientation;
	if (orientation == 'N')
	{
		set_vector(vector, 0.0, -1.0);
		set_vector(plane, 0.66, 0.0);
	}
	if (orientation == 'S')
	{
		set_vector(vector, 0.0, 1.0);
		set_vector(plane, -0.66, 0.0);
	}
	init_orientation_help(orientation, vector, plane);
}

void	init_orientation_help(char orientation, t_vector *vector,
		t_vector *plane)
{
	if (orientation == 'E')
	{
		set_vector(vector, 1.0, 0.0);
		set_vector(plane, 0.0, 0.66);
	}
	if (orientation == 'W')
	{
		set_vector(vector, -1.0, 0.0);
		set_vector(plane, 0.0, -0.66);
	}
}

void	init_start(t_game **game)
{
	char		**map;
	int			i;
	int			j;
	t_player	*player;

	i = 0;
	player = (*game)->player;
	map = (*game)->map->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (start_helper(map[i][j]))
			{
				player->player_pos->x = (double)j + 0.5;
				player->player_pos->y = (double)i + 0.5;
				player->orientation = map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
	return ;
}
