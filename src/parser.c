/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:49:26 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/04 13:13:30 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int validate_arg (char *str)
{
    char *extension;
    if (!str)
        return (0);
    extension = ft_strchr(str, 46);
    if (!extension)
        return (0);
    else if ((ft_strncmp(extension, ".cub", 4) != 0) || (ft_strlen(extension) != 4))
        print_error("Extension format not valid !");
    else
        return (1);
}

int validate_map(char *path)
{
    if (!validate_arg(path))
        return
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return 1;
    else
    {
        
    }
}