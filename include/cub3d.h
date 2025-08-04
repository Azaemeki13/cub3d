/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:16:03 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/04 17:29:45 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
#include <stdbool.h>

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768

#define ESCAPE_KEY 65307

typedef struct s_vector
{
    double x;
    double y;
} t_vector;

typedef struct s_player
{
    t_vector player_pos;
    t_vector camera_plane; //simulation of camera FOV
    t_vector vector_dir;
} t_player;

typedef struct s_ray
{
    t_vector ray_dir; //direction of the ray
    t_vector delta; //distance to next x or y grid line
    int step_dir_x; //+1 or -1
    int step_dir_y; //+1 or -1
    int map_x; //current tile x
    int map_y; //current tile y
    int wall_hit; //side x or y ? 0 or 1
    
} t_ray;

typedef struct s_rgb
{
    int r;
    int g;
    int b;
}   t_rgb;

typedef struct s_map
{
    char **content;
    bool pn_text;
    bool pe_text;
    bool ps_text;
    bool pw_text;
    t_rgb *ceiling;
    t_rgb *floor;
} t_map;

typedef struct s_game
{
    t_map *map;
    void *mlx;
    void *win;
} t_game;


//window_management.c

void create_window(void);
int close_window_hook(int keycode, t_game *game);
int close_window_x(t_game *game);

// error_management.c

void error_msg(const char *msg);

// parser.c

int validate_arg (char *str);
int validate_map(char *path, t_map **map);

// initialisation.c

void init_struct(t_game **game, char *path);
int count_lines(char *path);
void init_map(t_game **game, char *path);


#endif