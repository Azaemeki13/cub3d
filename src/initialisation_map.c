/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:49:34 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 12:01:27 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	is_begin(char *line, t_game **game, bool *begin)
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
			free_game_complete(game);
			exit(EXIT_FAILURE);
		}
		*begin = true;
	}
}

void	is_end(char *line, t_game **game, bool *end, bool *begin)
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
			free_game_complete(game);
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
		|| c == 'D'
		|| ft_isspace(c)))
		return (0);
	return (1);
}

void	line_checker(char *map_line, t_game **game)
{
    static bool	begin   = false;
    static bool	end     = false;
    int			i;

    is_begin(map_line, game, &begin);
    i = 0;
    while (map_line[i])
    {
        if (!map_char_check(map_line[i]) && map_line[i] != '\n')
        {
            error_msg("Unauthorized character in map.");
            free_game_complete(game);
            exit(EXIT_FAILURE);
        }
        i++;
    }
    is_end(map_line, game, &end, &begin);
}

void validate_player_count(t_game **game)
{
    char **map = (*game)->map->map;
    int player_count = 0;
    int x, y;
    
    y = 0;
    while (y < (*game)->map->map_height)
    {
        x = 0;
        while (x < (*game)->map->map_width && map[y][x])
        {
            if (ft_strchr("NSEW", map[y][x]))
                player_count++;
            x++;
        }
        y++;
    }
    
    if (player_count == 0)
    {
        error_msg("No player start position found in map.");
        free_game_complete(game);
        exit(EXIT_FAILURE);
    }
    else if (player_count > 1)
    {
        error_msg("Multiple player start positions found in map.");
        free_game_complete(game);
        exit(EXIT_FAILURE);
    }
}