/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <chsauvag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:52:22 by chsauvag          #+#    #+#             */
/*   Updated: 2025/08/04 12:56:06 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void error_msg(const char *msg)
{
        write(1, "Error\n", 6);
        write (1, msg, ft_strlen(msg));
        write(1, "\n", 1);
}