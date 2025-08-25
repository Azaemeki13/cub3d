/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:39:21 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/25 13:56:44 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	load_texture2(t_game **game, t_text *text, char *str)
{
	char	*nav;

	nav = ft_strndup(str, (size_t)ft_special_len(str, ' '));
	text->text_img = mlx_xpm_file_to_image((*game)->mlx, nav, &text->width,
			&text->height);
	texture_error_helper(text->text_img, nav, game);
	text->addr = mlx_get_data_addr(text->text_img, &text->bpp, &text->sl,
			&text->end);
	free(nav);
}

void	case_texture_helper(t_game **game, int option, char *str)
{
	t_map	*map;

	map = (*game)->map;
	if (option == 3)
		load_texture(game, map->so, str);
	else if (option == 4)
		load_texture2(game, map->we, str);
	case_texture_door(game, option, str);
}

void	load_texture(t_game **game, t_text *text, char *str)
{
	char	*nav;

	nav = ft_strndup(str, (size_t)ft_special_len(str, ' '));
	text->text_img = mlx_xpm_file_to_image((*game)->mlx, nav, &text->width,
			&text->height);
	texture_error_helper(text->text_img, nav, game);
	text->addr = mlx_get_data_addr(text->text_img, &text->bpp, &text->sl,
			&text->end);
	free(nav);
}

void	case_texture(t_game **game, int option, char *str)
{
	t_map	*map;

	map = (*game)->map;
	extension_validator(str, game);
	if (option == 1)
		load_texture(game, map->no, str);
	else if (option == 2)
		load_texture(game, map->ea, str);
	case_texture_helper(game, option, str);
}
