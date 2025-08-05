/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:39:16 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/05 10:26:11 by cauffret         ###   ########.fr       */
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

int case_texture(t_game **game, int option, char *str)
{
    
}

int case_rgb(t_game **game, int option, char *str)
{
    
}

int add_texture(t_game **game, int option, char *str)
{
    if (option >= 4)
        return((case_texture(game, option,str)));
    else
        return((case_rgb(game,option,str)));
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
            option = add_texture(game, option, str);
            if (!option)
            {
                free_game(game);
                error_msg("Check that texture path is correct.");
                exit(1);
            }
        }
    }
}
