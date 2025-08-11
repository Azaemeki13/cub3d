/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:32:37 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/11 11:39:02 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int validate_arg (char *str)
{
    char *extension;
    if(!str)
        return (0);
    extension = ft_strrchr(str, '.');
    if (!extension)
        return (0);
    else if ((ft_strncmp(extension, ".cub", 4) != 0) || (ft_strlen(extension) != 4))
        error_msg("Extension format not valid !");
    else
        return (1); 
    return(0);
}

int validate_map(char *path, t_game **game)
{
    if (!validate_arg(path))
        return (0);
    init_struct(game, path);
    return(1);
}

int validate_init(t_game **game, char *path)
{
    int i;
    
    i = validate_map(path, game);
    return(i);
}
