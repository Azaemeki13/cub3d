/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:49:34 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/08 09:24:17 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	is_begin(char *line, t_game **game, bool *begin)
{
	char	*p;

	p = line;
	if (!*begin)
	{
		while (ft_isspace(*p))
			p++;
		while (*p == '1' || ft_isspace(*p))
			p++;
		if (*p != '\n')
		{
			error_msg("map not valid.");
			free_game(game);
			exit(EXIT_FAILURE);
		}
		*begin = true;
	}
}

static void	is_end(char *line, t_game **game, bool *end, bool *begin)
{
	char	*p;

	p = line;
	if (*begin && !*end)
	{
		while (ft_isspace(*p))
			p++;
		while (*p == '1' || ft_isspace(*p))
			p++;
		if (!ft_isblank(p))
		{
			error_msg("map not valid.");
			free_game(game);
			exit(EXIT_FAILURE);
		}
		*end = true;
	}
}

int	map_char_check(char c)
{
	if (!(c == '1'
		|| c == '0'
		|| c == 'N'
		|| c == 'S'
		|| c == 'E'
		|| c == 'W'
		|| ft_isspace(c)))
		return (0);
	return (1);
}

void	line_checker(char *map_line, t_game **game)
{
	static bool	begin   = false;
	static bool	end     = false;
	static int	players = 0;
	int			i;

	is_begin(map_line, game, &begin);
	i = 0;
	while (map_line[i])
	{
		if (!map_char_check(map_line[i]) && map_line[i] != '\n')
		{
			error_msg("Unauthorized character in map.");
			free_game(game);
			exit(EXIT_FAILURE);
		}
		if (ft_strchr("NSEW", map_line[i]))
		{
			if (++players > 1)
			{
				error_msg("Multiple player start positions.");
				free_game(game);
				exit(EXIT_FAILURE);
			}
		}
		if (map_line[i] == '0' && !begin)
		{
			error_msg("Map not closed (hole on left).");
			free_game(game);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	is_end(map_line, game, &end, &begin);
	ft_printf("map line %s",map_line);
}
