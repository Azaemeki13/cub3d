/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:32:37 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/26 17:27:20 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_map_closed(char **map, int width, int height)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < width)
	{
		if (map[0][x] != '1' && map[0][x] != ' ')
			return (false);
		if (map[height - 1][x] != '1' && map[height - 1][x] != ' ')
			return (false);
		x++;
	}
	y = 0;
	while (y < height)
	{
		if (map[y][0] != '1' && map[y][0] != ' ')
			return (false);
		if (map[y][width - 1] != '1' && map[y][width - 1] != ' ')
			return (false);
		y++;
	}
	return (true);
}

int	validate_arg(char *str)
{
	char	*extension;

	if (!str)
		return (0);
	extension = ft_strrchr(str, '.');
	if (!extension)
		return (0);
	else if ((ft_strncmp(extension, ".cub", 4) != 0)
		|| (ft_strlen(extension) != 4))
		error_msg("Extension format not valid !");
	else
		return (1);
	return (0);
}

int	validate_map(char *path, t_game **game)
{
	if (!validate_arg(path))
		return (0);
	init_struct(game, path);
	return (1);
}

int	validate_init(t_game **game, char *path)
{
	int	i;

	i = validate_map(path, game);
	return (i);
}
