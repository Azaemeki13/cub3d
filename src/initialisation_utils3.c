/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:58:39 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 13:03:28 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rgb_error(t_game **game, char **str)
{
	error_msg("RGB format incorrect.");
	ft_free_string_array(str);
	free_game_complete(game);
	exit(1);
}

void	verify_rgb_number(t_game **game, char **verification)
{
	int		i;
	char	*nav;

	i = 0;
	while (i < 3)
	{
		nav = verification[i];
		while (*nav)
		{
			if (!ft_isdigit(*nav))
			{
				rgb_error(game, verification);
				return ;
			}
			nav++;
		}
		i++;
	}
}

char	**verify_syntax_rgb(t_game **game, char *str)
{
	char	**verification;
	char	*nav;
	int		i;

	verification = verify_syntax_rgb_helper(game, str);
	i = 0;
	while (i < 3)
	{
		nav = verification[i];
		if (!nav || !*nav)
			rgb_error(game, verification);
		while (*nav && ft_isspace(*nav))
			nav++;
		if (!*nav)
			rgb_error(game, verification);
		while (*nav)
		{
			if (!ft_isdigit(*nav) && !ft_isspace(*nav) && *nav != '\n')
				rgb_error(game, verification);
			nav++;
		}
		i++;
	}
	return (verification);
}

t_rgb	*add_rgb(t_game **game, char **rgb)
{
	t_rgb	*result;
	char	*trimmed;
	int		i;

	result = malloc(sizeof(t_rgb));
	if (!result)
		rgb_error(game, rgb);
	i = 0;
	while (i < 3)
	{
		trimmed = rgb[i];
		while (*trimmed && ft_isspace(*trimmed))
			trimmed++;
		rgb[i++] = trimmed;
	}
	result->r = ft_atoi(rgb[0]);
	result->g = ft_atoi(rgb[1]);
	result->b = ft_atoi(rgb[2]);
	if (result->r > 255 || result->g > 255 || result->b > 255 || result->r < 0
		|| result->g < 0 || result->b < 0)
	{
		free(result);
		rgb_error(game, rgb);
	}
	return (result);
}

void	malloc_texture(t_game **game)
{
	(*game)->map->no = malloc(sizeof(t_text));
	(*game)->map->door = malloc(sizeof(t_text));
	(*game)->map->ea = malloc(sizeof(t_text));
	(*game)->map->so = malloc(sizeof(t_text));
	(*game)->map->we = malloc(sizeof(t_text));
	ft_memset((*game)->map->no, 0, sizeof(t_text));
	ft_memset((*game)->map->ea, 0, sizeof(t_text));
	ft_memset((*game)->map->so, 0, sizeof(t_text));
	ft_memset((*game)->map->we, 0, sizeof(t_text));
	ft_memset((*game)->map->door, 0, sizeof(t_text));
}
