/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:16:03 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/04 13:14:25 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768

#define ESCAPE_KEY 65307

typedef struct s_game
{
    void *mlx;
    void *win;
} t_game;

void create_window(void);
void error_msg(const char *msg);
int close_window_hook(int keycode, t_game *game);
int close_window_x(t_game *game);

#endif