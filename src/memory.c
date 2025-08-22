/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:32:43 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 12:13:54 by cauffret         ###   ########.fr       */
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

void free_game_complete(t_game **game)
{
    if (!game || !*game || (*game)->cleanup_done)
        return ;
    
    (*game)->cleanup_done = 1;
    if ((*game)->img && (*game)->mlx)
        mlx_destroy_image((*game)->mlx, (*game)->img);
    if ((*game)->win && (*game)->mlx)
        mlx_destroy_window((*game)->mlx, (*game)->win);
    if ((*game)->player)
        ft_free_player((*game)->player);
    if ((*game)->map)
        ft_free_map_extended(&((*game)->map), (*game)->mlx);
    if ((*game)->doors)
        free((*game)->doors);
    if ((*game)->mlx)
    {
        mlx_destroy_display((*game)->mlx);
        free((*game)->mlx);
    }
    free(*game);
    *game = NULL;
}
