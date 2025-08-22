/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_map2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:52:28 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 12:53:13 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void validate_player_helper (t_game **game, int player_count)
{
    if (player_count == 0)
    {
        error_msg("No player start position found in map.");
        free_game_complete(game);
        exit(EXIT_FAILURE);
    }
    else if (player_count > 1)
    {
        error_msg("Multiple player start positions found in map.");
        free_game_complete(game);
        exit(EXIT_FAILURE);
    }
}