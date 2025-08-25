/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:35:56 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/25 17:06:19 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_door_valid(char **map, int x, int y, t_game *game)
{
	int	map_width;
	int	map_height;

	map_width = game->map->map_width;
	map_height = game->map->map_height;
	if (x <= 0 || x >= map_width - 1 || y <= 0 || y >= map_height - 1)
		return (false);
	return (has_valid_walls(map, x, y));
}

void	validate_doors(t_game **game)
{
	char	**map;
	int		x;
	int		y;

	map = (*game)->map->map;
	y = 0;
	while (y < (*game)->map->map_height)
	{
		x = 0;
		while (x < (*game)->map->map_width)
		{
			if (map[y][x] == 'D' || map[y][x] == 'd')
			{
				if (!is_door_valid(map, x, y, *game))
				{
					error_msg("Door not properly placed between walls.");
					free_game_complete(game);
					exit(EXIT_FAILURE);
				}
			}
			x++;
		}
		y++;
	}
}
