/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:36:40 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/12 09:36:14 by cauffret         ###   ########.fr       */
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
    t_text *text;

    map = (*game)->map;
    if (option == 3)
    {
        text = map->so;
        nav = ft_strndup(str, (size_t)ft_special_len(str, ' '));
        text->text_img = mlx_xpm_file_to_image((*game)->mlx, nav, &text->width, &text->height);
        texture_error_helper(text->text_img, nav, game);
        text->addr = mlx_get_data_addr(text->text_img, &text->bpp, &text->sl, &text->end);
    } 
    if (option == 4)
    {
        text = map->we;
        nav = ft_strndup(str, (size_t)ft_special_len(str, ' '));
        text->text_img = mlx_xpm_file_to_image((*game)->mlx, nav, &text->width, &text->height);
        texture_error_helper(text->text_img, nav, game);
        text->addr = mlx_get_data_addr(text->text_img, &text->bpp, &text->sl, &text->end);
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

    init_start(game); 
    init_orientation(game);
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