/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:26:20 by pargev            #+#    #+#             */
/*   Updated: 2026/01/27 18:32:04 by pargev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_str_only(const char *s, const char *allowed)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (ft_strchr(allowed, s[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}