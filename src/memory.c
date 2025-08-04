/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:32:38 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/04 15:30:07 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free_string_array(char **arr)
{
        int	i;
        if (!arr)
                return ;
        i = 0;
        while (arr[i])
        {
                free(arr[i]);
                arr[i] = NULL;
                i++;
        }
        free(arr);
}

void ft_free_rgb(t_rgb *rgb)
{
    if (!rgb)
        return;
    free(rgb);
}

void ft_free_map(t_map **map)
{
    if (!map || !*map)
        return;

    ft_free_string_array((*map)->content);
    ft_free_rgb((*map)->ceiling);
    ft_free_rgb((*map)->floor);
    free(*map);
    *map = NULL;
}

void free_game(t_game **game)
{
    if (!game || !*game)
        return;

    if ((*game)->map)
        ft_free_map(&((*game)->map));
    free(*game);
    *game = NULL;
}
