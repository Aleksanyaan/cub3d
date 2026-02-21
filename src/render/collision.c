/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 20:31:08 by zaleksan          #+#    #+#             */
/*   Updated: 2026/02/21 14:33:42 by pargev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(double x, double y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BLOCK_SIZE);
	map_y = (int)(y / BLOCK_SIZE);
	if (map_y < 0 || !game->config.map[map_y])
		return (1);
	if (map_x < 0 || game->config.map[map_y][map_x] == '\0')
		return (1);
	return (game->config.map[map_y][map_x] == '1');
}
