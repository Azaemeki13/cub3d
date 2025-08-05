/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:32:37 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/05 09:36:29 by cauffret         ###   ########.fr       */
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

int validate_map(char *path, t_map **map)
{
    int fd;
    if (!validate_arg(path))
        return (0);
    init_map(map, path);
}
