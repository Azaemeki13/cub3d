/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:39:16 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/25 13:39:40 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	texture_helper(char *str)
{
	if (!str)
		return (0);
	if ((ft_strncmp(str, "NO", 2) == 0) && ft_isspace(*(str + 2)))
		return (1);
	else if ((ft_strncmp(str, "EA", 2) == 0) && ft_isspace(*(str + 2)))
		return (2);
	else if ((ft_strncmp(str, "SO", 2) == 0) && ft_isspace(*(str + 2)))
		return (3);
	else if ((ft_strncmp(str, "WE", 2) == 0) && ft_isspace(*(str + 2)))
		return (4);
	else if ((ft_strncmp(str, "C", 1) == 0) && ft_isspace(*(str + 1)))
		return (5);
	else if ((ft_strncmp(str, "F", 1) == 0) && ft_isspace(*(str + 1)))
		return (6);
	else if ((ft_strncmp(str, "D", 1) == 0) && ft_isspace(*(str + 1)))
		return (7);
	else
		return (0);
}

void	case_rgb(t_game **game, int option, char *str)
{
	char	**rgb;

	rgb = verify_syntax_rgb(game, str);
	if (option == 5)
		(*game)->map->ceiling = add_rgb(game, rgb);
	if (option == 6)
		(*game)->map->floor = add_rgb(game, rgb);
	ft_free_string_array(rgb);
}

void	add_texture(t_game **game, int option, char *str)
{
	if (option < 5 || option == 7)
		case_texture(game, option, str);
	else
		case_rgb(game, option, str);
}

void	validate_textures(char *str, t_game **game)
{
	int	option;

	while (ft_isspace(*str))
		str++;
	option = texture_helper(str);
	if (option)
	{
		while (ft_isalpha(*str))
			str++;
		while (ft_isspace(*str))
			str++;
		add_texture(game, option, str);
	}
	else
	{
		error_msg("Non texture or RGB or map found.");
		free_game_complete(game);
		exit(1);
	}
}
