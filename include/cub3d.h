/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:16:03 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/08 10:14:07 by cauffret         ###   ########.fr       */
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
# include <stdbool.h>

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768

#define MAP_WIDTH 12
#define MAP_HEIGHT 12

#define ESCAPE_KEY 65307
#define UP 65362
#define DOWN 65364
#define ROTATE_LEFT 65361
#define ROTATE_RIGHT 65363

typedef struct s_vector
{
    double x;
    double y;
} t_vector;

typedef struct s_player
{
    t_vector *player_pos;
    t_vector *camera_plane; //simulation of camera FOV
    t_vector *vector_dir;
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
    char **map;
    bool pn_text;
    void *pn_img;
    bool pe_text;
    void *pe_img;
    bool ps_text;
    void *ps_img;
    bool pw_text;
    void *pw_img;
    int height;
    int width;
    t_rgb *ceiling;
    t_rgb *floor;
} t_map;

typedef struct s_game 
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    t_player *player;
    t_map   *map;
} t_game;

typedef struct s_drawrange
{
    int start;
    int end;
    int height;
}t_drawrange;

//window_management.c

void create_window(t_game *game);
int close_window_hook(int keycode, t_game *game);
int close_window_x(t_game *game);

// error_management.c

void error_msg(const char *msg);

// parser.c

int validate_arg (char *str);
int validate_map(char *path, t_game **game);
int validate_init(t_game **game, char *path);

// memory.c
    
void	ft_free_string_array(char **arr);
void ft_free_rgb(t_rgb *rgb);
void ft_free_map(t_map **map);
void free_game(t_game **game);

// initialisation.c

void init_struct(t_game **game, char *path);
int count_lines(char *path);
int map_details(char *line);
void check_texture_files(t_game **game);
void init_map(t_game **game, char *path);

//initialisation_utils.c

int texture_helper(char *str);
void case_texture(t_game **game, int option, char *str);
void case_rgb(t_game **game, int option, char *str);
void add_texture(t_game **game, int option, char *str);
void validate_textures(char *str, t_game **game);

//initialisation_utils2.c

void extension_validator(char *str, t_game **game);
void case_texture_helper(t_game **game, int option, char *str);
void texture_error_helper(void *image, char *nav, t_game **game);
void init_player(t_game **game);
void map_pointer(t_game **game, int i);

//initialisation_utils3.c

void rgb_error(t_game **game, char **str);
void verify_rgb_number(t_game **game, char **verification);
char **verify_syntax_rgb(t_game **game, char *str);
t_rgb *add_rgb(t_game **game, char **rgb);

//initialisation_map.c

int	map_char_check(char c);
void	line_checker(char *map_line, t_game **game);

// miscs.c 

int ft_isspace(char c);
int ft_isblank(char *str);
int ft_special_len(char *str, int separator);
char	*ft_strndup(const char *s, size_t n);
int count_strings(char **str);

// raycasting_engine.c

double ray_casting(int x, t_player *player);
t_drawrange calculate_draw_range(double perp_wall_dist);
void draw_vertical_line(t_game *game_data, int x, int start, int end, int color);

// rendering.c

int	render_frame(void *param);

//dumb_shit_to_get_rid_of_later.c

int get_shade_color(int base_color, double distance);
int create_rgb_color(int r, int g, int b);
int key_hook(int keycode, t_game *game);

#endif
