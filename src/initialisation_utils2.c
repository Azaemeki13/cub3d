/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:36:40 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/07 14:27:20 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void extension_validator(char *str, t_game **game)
{
    char *extension;

    extension = ft_strrchr(str, '.');
    if (!extension)
    {
        error_msg("Wrong extension.");
        free_game(game);
        exit(1);
    }
    if ((ft_strncmp(extension, ".xpm", 4) != 0) && (!ft_isblank(str + 4)))
    {
        error_msg("Wrong extension || Line after expansion not blank.");
        free_game(game);
        exit(1);
    }
}

void case_texture_helper(t_game **game, int option, char *str)
{
    char *nav = NULL; 
    t_map *map;

    map = (*game)->map;
    if (option == 3)
    {
        nav = ft_strndup(str, ((size_t)ft_special_len(str, ' ')));
        map->ps_img = mlx_xpm_file_to_image((*game)->mlx, nav, &map->width, &map->height);
        texture_error_helper(map->ps_img, nav, game);
        map->ps_text = true;
    } 
    if (option == 4)
    {
        nav = ft_strndup(str, (size_t)ft_special_len(str, ' '));
        map->pw_img = mlx_xpm_file_to_image((*game)->mlx, nav, &map->width, &map->height);
        texture_error_helper(map->pw_img, nav, game);
        map->pw_text = true;
    }
    if (nav)
        free(nav);
}

void texture_error_helper(void *image, char *nav, t_game **game)
{
    if (!image)
    {
        error_msg("xpm file not found.");
        free(nav);
        free_game(game);
        exit(1); 
    }
}
