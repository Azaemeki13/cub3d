/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:56:50 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/25 14:18:57 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_texture(t_text *texture, void *mlx)
{
	if (!texture)
		return ;
	if (texture->text_img && mlx)
		mlx_destroy_image(mlx, texture->text_img);
	free(texture);
}

void	ft_free_player(t_player *player)
{
	if (!player)
		return ;
	if (player->player_pos)
		free(player->player_pos);
	if (player->camera_plane)
		free(player->camera_plane);
	if (player->vector_dir)
		free(player->vector_dir);
	free(player);
}

void	ft_free_map_extended(t_map **map, void *mlx)
{
	if (!map || !*map)
		return ;
	ft_free_string_array((*map)->content);
	ft_free_texture((*map)->no, mlx);
	ft_free_texture((*map)->ea, mlx);
	ft_free_texture((*map)->so, mlx);
	ft_free_texture((*map)->we, mlx);
	ft_free_texture((*map)->door, mlx);
	ft_free_rgb((*map)->ceiling);
	ft_free_rgb((*map)->floor);
	free(*map);
	*map = NULL;
}
