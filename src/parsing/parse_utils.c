/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:38:56 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 13:41:37 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	parse_position(char **map, int *x_position, int *y_position)
{
	int	x;
	int	y;

	if (!map)
		return ;
	*x_position = -1;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player(map[y][x]))
			{
				if (*x_position >= 0)
					return ((void)(*x_position = -1));
				*x_position = x;
				*y_position = y;
			}
			++x;
		}
		++y;
	}
}

int	parse_map_rows(char **config_text, char **map, int start)
{
	int	i;

	i = 0;
	while (config_text[start + i] && config_text[start + i][0] != '\n')
	{
		if (!ft_str_only(config_text[start + i], " \n10NWES"))
			return (0);
		map[i] = ft_strdup_free(ft_strtrim(config_text[start + i], "\n"));
		i++;
	}
	while (config_text[start + i])
	{
		if (!ft_str_only(config_text[start + i], " \n"))
			return (0);
		++i;
	}
	return (1);
}
