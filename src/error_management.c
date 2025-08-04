/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:52:22 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/04 14:04:49 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void error_msg(const char *msg)
{
        write(2, "Error:\n", 6);
        write (2, msg, ft_strlen(msg));
        write(2, "\n", 1);
}

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

void ft_free_map(t_map **map)
{
    if (!map || !*map)
        return;

    ft_free_string_array((*map)->content);
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
