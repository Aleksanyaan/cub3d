/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 20:31:08 by zaleksan          #+#    #+#             */
/*   Updated: 2026/02/10 20:50:28 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(double x, double y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BLOCK_SIZE);
	map_y = (int)(y / BLOCK_SIZE);
	if (map_y < 0 || !game->map[map_y])
		return (1);
	if (map_x < 0 || game->map[map_y][map_x] == '\0')
		return (1);
	return (game->map[map_y][map_x] == '1');
}

void	free_all(t_game *game)
{
	if (!game)
		exit(1);
	free(game->player);
	// free_map(game->map);
	free(game);
}

void	cleanup(t_game *game)
{
if (game->img)
    mlx_destroy_image(game->mlx, game->img);
if (game->win)
    mlx_destroy_window(game->mlx, game->win);
if (game->mlx)
    free(game->mlx);
}
