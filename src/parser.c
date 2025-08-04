/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:49:26 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/04 14:10:10 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int validate_arg (char *str)
{
    char *extension;
        return (0);
    extension = ft_strchr(str, 46);
    if (!extension)
        return (0);
    else if ((ft_strncmp(extension, ".cub", 4) != 0) || (ft_strlen(extension) != 4))
        error_msg("Extension format not valid !");
    else
        return (1);
}

void init_struct(t_game **game, char *path)
{
    *game = malloc(sizeof(*game));
    ft_memset(*game, 0, sizeof(*game));
    (*game)->map = malloc(sizeof(t_map));
    init_map(game, path);

}

void init_map(t_game **game, char *path)
{
    t_map *map;
    int fd;
    int i;

    i = 0;
    map = (*game)->map;
    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        close(fd);
        error_msg("Cannot open file.");
        free_game(game);
        exit(1);
    }
    while(get_next_line())
}

int validate_map(char *path, t_map **map)
{
    int fd;

    if (!validate_arg(path))
        return (0);
    init_map(map, path);
}
