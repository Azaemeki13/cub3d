/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:01:09 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 14:09:12 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void validate_all_textures_helper(t_game **game, t_map *map)
{
    if (!map->we || !map->we->text_img)
    {
        error_msg("Missing WE texture path.");
        free_game_complete(game);
        exit(1);
    }
    if (!map->door || !map->door->text_img)
    {
        error_msg("Missing DOOR texture path.");
        free_game_complete(game);
        exit(1);
    }
    if (!map->ceiling)
    {
        error_msg("Missing ceiling color (C).");
        free_game_complete(game);
        exit(1);
    }
    if (!map->floor)
    {
        error_msg("Missing floor color (F).");
        free_game_complete(game);
        exit(1);
    }
}

void validate_all_textures_present(t_game **game)
{
    t_map *map;
    
    map = (*game)->map;
    if (!map->no || !map->no->text_img)
    {
        error_msg("Missing NO texture path.");
        free_game_complete(game);
        exit(1);
    }
    if (!map->so || !map->so->text_img)
    {
        error_msg("Missing SO texture path.");
        free_game_complete(game);
        exit(1);
    }
    if (!map->ea || !map->ea->text_img)
    {
        error_msg("Missing EA texture path.");
        free_game_complete(game);
        exit(1);
    }
    validate_all_textures_helper(game, map);
}

void init_map_helper(t_game **game, char *path, int *i)
{
    *i = count_lines(path);
    if (*i == 0)
    {
        error_msg("Cannot open file / File empty.");
        free_game_complete(game);
        exit(1);
    }
}
