/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:19:25 by cauffret          #+#    #+#             */
/*   Updated: 2025/08/05 10:26:12 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int ft_isspace(char c)
{
    if (!c)
        return (0);
    else if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == 'r')
        return (1);
    return (0);
}
int ft_isblank(char *str)
{
    if (!str)
        return (0);
    int i;

    i = 0;
    while((ft_isspace(str[i])) || str[i] == '\n')
        i++;
    if (i != (ft_strlen(str)))
        return(0);
    else
        return(1);
}
