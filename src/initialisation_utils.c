/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:39:16 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/05 13:48:49 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int texture_helper(char *str)
{
    if (!str)
        return (0);
    if ((ft_strncmp(str, "NO", 2) == 0) && ft_isspace(*(str+2)))
        return (1);
    else if ((ft_strncmp(str, "EA", 2) == 0) && ft_isspace(*(str+2)))
        return (2);
    else if ((ft_strncmp(str, "SO", 2) == 0) && ft_isspace(*(str+2)))
        return (3);
    else if ((ft_strncmp(str, "WE", 2) == 0) && ft_isspace(*(str+2)))
        return (4);
    else if ((ft_strncmp(str, "C", 1) == 0) && ft_isspace(*(str+1)))
        return (5);
    else if ((ft_strncmp(str, "F", 1) == 0) && ft_isspace(*(str+1)))
        return (6);
    else
        return(0);
}


void case_texture(t_game **game, int option, char *str)
{
    char *nav;
    t_map *map;
    
    map = (*game)->map;
    extension_validator(str, game);    
    if (option == 1)
    {
        nav = ft_strndup(str, (size_t)ft_special_len(str, ' '));
        map->pn_img = mlx_xpm_file_to_image((*game)->mlx, nav, &map->width, &map->height);
        texture_error_helper(map->pn_img, nav, game);
        map->pn_text = true;
    }
    if (option == 2)
    {
        nav = ft_strndup(str, (size_t)ft_special_len(str, ' '));
        map->pe_img = mlx_xpm_file_to_image((*game)->mlx, nav, &map->width, &map->height);
        texture_error_helper(map->pe_img, nav, game);
        map->pe_text = true;
    }
    case_texture_helper(game, option, str);
    free(nav);
}

void case_rgb(t_game **game, int option, char *str)
{
    char **rgb;
    
    rgb = verify_syntax_rgb(game, str);
    if (option == 5)
        (*game)->map->ceiling = add_rgb(game, rgb);

    if (option == 6)
        (*game)->map->floor = add_rgb(game, rgb);
    ft_free_string_array(rgb);
}

void add_texture(t_game **game, int option, char *str)
{
    if (option >= 5)
        case_texture(game, option,str);
    else
        case_rgb(game,option,str);
}

void validate_textures(char *str, t_game **game)
{
    int i;
    int option;
    
    i = 0;
    while(*str)
    {
        while(ft_isspace(*str))
            str++;
        option = texture_helper(str);
        if (option)
        {
            while(ft_isalpha(*str))
                str++;
            while(ft_isspace(*str))
                str++;
            add_texture(game, option, str);
        }
        else
            break ;
    }
    return ;
}
