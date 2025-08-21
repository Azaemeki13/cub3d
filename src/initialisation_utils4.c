/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:16:22 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/21 16:47:54 by chsauvag         ###   ########.fr       */
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
    t_vector *plane;

    vector = (*game)->player->vector_dir;
    plane = (*game)->player->camera_plane;
    orientation = (*game)->player->orientation;
        
    if (orientation == 'N')
    {
        set_vector(vector, 0.0, -1.0);
        set_vector(plane, 0.66, 0.0);
    }
    if (orientation == 'S')
    {
        set_vector(vector, 0.0, 1.0);
        set_vector(plane, -0.66, 0.0);
    }
    if (orientation == 'E')
    {
        set_vector(vector, 1.0, 0.0);
        set_vector(plane, 0.0, 0.66);
    }
    if (orientation == 'W')
    {
        set_vector(vector, -1.0, 0.0);
        set_vector(plane, 0.0, -0.66);
    }
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
                player->player_pos->x = (double)j + 0.5;  // Center in grid cell
                player->player_pos->y = (double)i + 0.5;  // Center in grid cell
                player->orientation = map[i][j];
                return;
            }
            j++;
        }
        i++;
    }
    return ;
}

void calculate_map_size(t_game **game)
{
    char **map;
    int i;
    int j;
    int max_length;
    int y;
    int len;
    int x;
    char *new_line;

    j = 0;
    max_length = 0;
    map = (*game)->map->map;
    while(map[j])
    {
        if (ft_isblank(map[j]))
            break;
        i = 0;
        while(map[j][i] && map[j][i] != '\n')
            i++;
        if (i > max_length)
            max_length = i;
        j++;
    }
    (*game)->map->map_height = j;
    (*game)->map->map_width = max_length;
    y = 0;
    while (y < j)
    {
        len = ft_strlen(map[y]);
        if (len < max_length)
        {
            new_line = ft_calloc(max_length + 1, sizeof(char));
            ft_strlcpy(new_line, map[y], len + 1);
            x = len;
            while (x < max_length)
            {
                new_line[x] = ' ';
                x++;
            }
            new_line[max_length] = '\0';
            free(map[y]);
            map[y] = new_line;
        }
        y++;
    }
}