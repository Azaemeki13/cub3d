/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:23:36 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/05 10:26:10 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void init_struct(t_game **game, char *path)
{
    *game = malloc(sizeof(*game));
    ft_memset(*game, 0, sizeof(*game));
    (*game)->map = malloc(sizeof(t_map));
    init_map(game, path);

}

int count_lines(char *path)
{
    int fd;
    int result;

    result = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        close(fd);
        return (0);
    }
    while (get_next_line(fd) != NULL)
        result++;
    close(fd);
    return(result);
}

int map_details(char *line)
{
    int i;
    
    i = 0;
    while(ft_isspace(line[i]))
        i++;
    if (line[i] && line[i] == '1')
        return (1);
    else
        return(0);
}

void check_texture_files(t_game **game)
{
    t_map *map;
    int i;

    i = 0;
    map = (*game)->map;
    while(map->content[i])
    {
        while(!map_details(map->content[i]))
        {
            if (!ft_isblank(map->content[i]))
                validate_textures()
        }
    }
}

void init_map(t_game **game, char *path)
{
    t_map *map;
    int fd;
    int i;
    int count;

    i = 0;
    map = (*game)->map;
    count = count_lines(path);
    if (count = 0)
    {
        error_msg("Cannot open file / File empty.");
        free_game(game);
        exit(1);
    }
    fd = open(path, O_RDONLY);
    map->content = malloc(sizeof(char *) * (count + 1));
    map->content[count] = NULL;
    while(i != count)
        map->content[i++] = get_next_line(fd);
    check_textures_files(game);
    
}
