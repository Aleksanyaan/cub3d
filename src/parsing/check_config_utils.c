/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:27:13 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 13:28:58 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_row_border(char **map, int i, int j)
{
	if (i == 0 || !map[i + 1])
		return (map[i][j] != '1');
	return (0);
}

static int	check_col_border(char **map, int i, int j)
{
	if (j == 0 || !map[i][j + 1])
		return (map[i][j] != '1');
	return (0);
}

static int	check_neighbor_len(char **map, int i, int j)
{
	if (i > 0 && map[i][j + 1])
		if (ft_strlen(map[i - 1]) < (size_t)j + 2)
			return (1);
	if (map[i + 1] && map[i][j + 1])
		if (ft_strlen(map[i + 1]) < (size_t)j + 2)
			return (1);
	return (0);
}

int	check_cell(char **map, int i, int j)
{
	if (map[i][j] == ' ')
		return (check_border(map, i, j));
	if (check_row_border(map, i, j) || check_col_border(map, i, j))
		return (1);
	if (ft_strchr("0NSWE", map[i][j]) > 0)
		return (check_neighbor_len(map, i, j));
	return (0);
}
