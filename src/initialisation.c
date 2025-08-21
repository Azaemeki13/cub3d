/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:23:36 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/21 14:26:25 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void init_struct(t_game **game, char *path)
{
    *game = malloc(sizeof(**game));
    ft_memset(*game, 0, sizeof(*game));
    (*game)->mlx = mlx_init();
    (*game)->map = malloc(sizeof(t_map));
    ft_memset((*game)->map, 0, sizeof(t_map));
    malloc_texture(game);
    init_map(game, path);
    init_player(game);
    doors_init(*game);
    (*game)->buttons.w = 0;
    (*game)->buttons.s = 0;
    (*game)->buttons.q = 0;
    (*game)->buttons.d = 0;
    (*game)->buttons.rotate_left = 0;
    (*game)->buttons.rotate_right = 0;
    (*game)->game_pause = 0;
    (*game)->show_minimap = 1;
    (*game)->mouse_sens = 0.0008;
    (*game)->last_mouse_x = WIN_WIDTH / 2;
    (*game)->hit_tile = 0;
    (*game)->side_out = 0;
    (*game)->wall_x = 0.0;
    (*game)->ray_dir.x = 0.0;
    (*game)->ray_dir.y = 0.0;
    (*game)->img = NULL;
    (*game)->addr = NULL;
    (*game)->bits_per_pixel = 0;
    (*game)->line_length = 0;
    (*game)->endian = 0;
}

int count_lines(char *path)
{
    int fd;
    int result;
    char *line;

    result = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (0);
    while ((line = get_next_line(fd)) != NULL)
    {
        free(line);
        result++;
    }
    close(fd);
    return(result);
}

int map_details(char *line)
{
    int i;
    
    i = 0;
    if (!line)
        return(0);
    while(line[i] && ft_isspace(line[i]))
        i++;
    if (line[i] && line[i] == '1')
        return (1);
    else
        return(0);
}

void validate_all_textures_present(t_game **game)
{
    t_map *map = (*game)->map;
    
    if (!map->no || !map->no->text_img)
    {
        error_msg("Missing NO texture path.");
        free_game(game);
        exit(1);
    }
    if (!map->so || !map->so->text_img)
    {
        error_msg("Missing SO texture path.");
        free_game(game);
        exit(1);
    }
    if (!map->ea || !map->ea->text_img)
    {
        error_msg("Missing EA texture path.");
        free_game(game);
        exit(1);
    }
    if (!map->we || !map->we->text_img)
    {
        error_msg("Missing WE texture path.");
        free_game(game);
        exit(1);
    }
    if (!map->door || !map->door->text_img)
    {
        error_msg("Missing DOOR texture path.");
        free_game(game);
        exit(1);
    }
    if (!map->ceiling)
    {
        error_msg("Missing ceiling color (C).");
        free_game(game);
        exit(1);
    }
    if (!map->floor)
    {
        error_msg("Missing floor color (F).");
        free_game(game);
        exit(1);
    }
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
                validate_textures(map->content[i], game);
            i++;
        }
        while(ft_isblank(map->content[i]))
            i++;
        if (!map_details(map->content[i]))
            error_msg("Line not blank and map incorrect.");
        map_pointer(game, i);
        while(map_details(map->content[i]) && map->content[i])
            line_checker(map->content[i++], game);
        break;
    }
    validate_all_textures_present(game);
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
    if (count == 0)
    {
        error_msg("Cannot open file / File empty.");
        free_game(game);
        exit(1);
    }
    fd = open(path, O_RDONLY);
    map->content = malloc(sizeof(char *) * (count + 1));
    map->content[count] = NULL;
    map->height = 200;
    map->width = 200;
    while(i != count)
        map->content[i++] = get_next_line(fd);
    check_texture_files(game);
    calculate_map_size(game);
    validate_doors(game);
    validate_player_count(game); // Add this line
    (*game)->mouse_sens = 0.0008;
    (*game)->last_mouse_x = WIN_WIDTH / 2;
    close(fd);
}
