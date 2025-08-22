/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils3_helper.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:00:28 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/22 13:03:04 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **verify_syntax_rgb_helper(t_game **game, char *str)
{
    char **verification;
    
    verification = ft_split(str, ',');
    if (!verification)
        rgb_error(game, verification);
    if (count_strings(verification) != 3)
        rgb_error(game, verification);
    return (verification);
}
