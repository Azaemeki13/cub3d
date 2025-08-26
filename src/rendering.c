/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:58:49 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/26 16:55:22 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	main_stripe_loop_utils(t_game *game, t_stripe *stripe,
		int ceiling_color, int floor_color)
{
	if (stripe->start < 0)
		stripe->start = 0;
	if (stripe->end >= WIN_HEIGHT)
		stripe->end = WIN_HEIGHT - 1;
	if (stripe->start > 0)
	{
		game->current_color = ceiling_color;
		draw_vertical_line(game, stripe->x, 0, stripe->start - 1);
	}
	stripe->tex = get_wall_text(stripe->wall_dir, &game);
	game->current_tex = stripe->tex;
	if (stripe->start <= stripe->end)
	{
		draw_textures(&game, stripe->x, stripe->start, stripe->end);
		if (stripe->end < WIN_HEIGHT - 1)
		{
			game->current_color = floor_color;
			draw_vertical_line(game, stripe->x, stripe->end + 1, WIN_HEIGHT
				- 1);
		}
	}
}

void	main_stripe_loop(t_game *game, int ceiling_color, int floor_color)
{
	t_stripe	stripe;

	stripe.x = 0;
	while (stripe.x < WIN_WIDTH)
	{
		stripe.perp_dist = ray_casting(stripe.x, &stripe.wall_dir, game,
				&game->wall_x);
		game->range = calculate_draw_range(stripe.perp_dist, game);
		stripe.start = game->range.start;
		stripe.end = game->range.end;
		main_stripe_loop_utils(game, &stripe, ceiling_color, floor_color);
		stripe.x++;
	}
}

int	render_frame(void *param)
{
	t_game	*game;
	int		ceiling_color;
	int		floor_color;

	game = (t_game *)param;
	game_update(game);
	if (!game->img)
	{
		game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
		game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
				&game->line_length, &game->endian);
	}
	set_bytespp(&game);
	ceiling_color = create_rgb_color(game->map->ceiling->r,
			game->map->ceiling->g, game->map->ceiling->b);
	floor_color = create_rgb_color(game->map->floor->r, game->map->floor->g,
			game->map->floor->b);
	ft_memset(game->addr, 0, WIN_HEIGHT * game->line_length);
	main_stripe_loop(game, ceiling_color, floor_color);
	if (game->show_minimap)
		draw_minimap(game);
	draw_reticle(&game, 5, 10);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	get_wall_direction(int side, int step_x, int step_y)
{
	if (side == 0)
	{
		if (step_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (step_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

int	game_update(t_game *game)
{
	t_keymap	keys;
	double		rotation_speed;
	double		move_speed;

	rotation_speed = 0.1;
	move_speed = 0.05;
	keys = game->buttons;
	doors_update(game, 0.0);
	if (keys.w)
		move_forward(game, move_speed);
	if (keys.s)
		move_backward(game, move_speed);
	if (keys.q)
		move_left(game, move_speed);
	if (keys.d)
		move_right(game, move_speed);
	if (keys.rotate_left)
		rotate_left_calc(game, rotation_speed);
	if (keys.rotate_right)
		rotate_right_calc(game, rotation_speed);
	return (0);
}
