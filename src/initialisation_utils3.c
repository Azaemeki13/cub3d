/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:58:39 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/12 13:25:53 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void rgb_error(t_game **game, char **str)
{
    error_msg("rgb format incorrect.");
    ft_free_string_array(str);
    free_game(game);
    exit(1);
}

void verify_rgb_number(t_game **game, char **verification)
{
    int i;
    char *nav;
    
    i = 0;
    while(i < 2)
    {
        nav = verification[i];
        while(*verification[i])
        {
            if (!ft_isdigit(*verification[i]) && *verification[i] != ',')
                rgb_error(game, verification);
            verification[i]++;
        }
        verification[i] = nav;
        i++;
    }
}

char **verify_syntax_rgb(t_game **game, char *str)
{
    char **verification;
    char *nav;

    verification = ft_split(str, ',');
    if (!verification)
        rgb_error(game, verification);
    if ((count_strings(verification) > 3))
        rgb_error(game, verification);
    nav = verification[2];
    while(ft_isdigit(*verification[2]))
        verification[2]++;
    if (!ft_isblank(verification[2]))
        rgb_error(game, verification);
    verification[2] = nav;
    return (verification);
}

t_rgb *add_rgb(t_game **game, char **rgb)
{
    t_rgb *result;

    result = malloc(sizeof(t_rgb));
    result->r = ft_atoi(rgb[0]);
    result->g = ft_atoi(rgb[1]);
    result->b = ft_atoi(rgb[2]);
    if (result->r > 255 || result->g > 255 || result->b > 255)
    {
        free(result);
        rgb_error(game, rgb);
    }
    return (result);
}

void  malloc_texture(t_game **game)
{
    (*game)->map->no = malloc(sizeof(t_text));
    (*game)->map->ea = malloc(sizeof(t_text));
    (*game)->map->so = malloc(sizeof(t_text));
    (*game)->map->we = malloc(sizeof(t_text));
    ft_memset((*game)->map->no, 0 , sizeof(t_text));
    ft_memset((*game)->map->ea, 0 , sizeof(t_text));
    ft_memset((*game)->map->so, 0 , sizeof(t_text));
    ft_memset((*game)->map->we, 0 , sizeof(t_text));
}