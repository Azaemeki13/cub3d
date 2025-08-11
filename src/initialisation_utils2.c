/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:36:40 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/11 13:13:45 by cauffret         ###   ########.fr       */
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

void init_player(t_game **game)
{
    t_player *player;
    
    (*game)->player = malloc(sizeof(t_player));
    player = (*game)->player;
    player->player_pos = malloc(sizeof(t_vector));
    player->camera_plane = malloc(sizeof(t_vector));
    player->vector_dir = malloc(sizeof(t_vector));
    player->player_pos->x = 6.0;
    player->player_pos->y = 3.0;
    player->vector_dir->x = -1.0;
    player->vector_dir->y = 0.0;
    player->camera_plane->x = 0.0;
    player->camera_plane->y = 0.66;
    init_orientation(game);
    init_start(game);
}

void map_pointer(t_game **game, int i)
{
    t_map *map;
    char **nav;
    int d;

    d = -1;
    map = (*game)->map;
    nav = map->content;
    while (++d < i)
        nav++;
    map->map = nav;
}
