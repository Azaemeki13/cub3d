/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:52:22 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/04 15:30:06 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void error_msg(const char *msg)
{
        write(2, "Error:\n", 6);
        write (2, msg, ft_strlen(msg));
        write(2, "\n", 1);
}
