/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:16:22 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/08 11:31:17 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int start_helper(char c)
{
    if (c == 'N' || c == 'E' || c == 'S'
    || c == 'W')
        return(1);
    return(0);
}

void set_vector(t_vector *vector, double x, double y)
{
    vector->x = x;
    vector->y = y;
}

void init_orientation(t_game **game)
{
    char orientation;
    t_vector *vector;

    vector =  (*game)->player->vector_dir;
    orientation =(*game)->player->orientation;
    if (orientation == 'N')
        set_vector(vector, 0.0, 1.0);
    if (orientation == 'S')
        set_vector(vector, 0.0, -1.0);
    if (orientation == 'E')
        set_vector(vector, 1.0, 0.0);
    if (orientation == 'W')
        set_vector(vector, -1.0, 0.0);
}

void init_start(t_game **game)
{
    char **map;
    int i;
    int j;
    t_player *player;
    
    i = 0;
    player = (*game)->player;
    map = (*game)->map->map;
    while(map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if(start_helper(map[i][j]))
            { 
                player->player_pos->x = j;
                player->player_pos->y = i;
                player->orientation = map[i][j];
                return;
            }
            j++;
        }
        i++;
    }
    return ;
}
