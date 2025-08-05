/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:32:37 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/05 09:35:09 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int validate_map(char *path, t_map **map)
{
    int fd;
    if (!validate_arg(path))
        return (0);
    init_map(map, path);
}
