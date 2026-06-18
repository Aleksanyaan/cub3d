/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:47:52 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 14:48:22 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_game *game)
{
	if (!game)
		exit(1);
	free_all(game);
	exit(0);
}

void	init_struct(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->data = NULL;
	game->player = NULL;
	game->bpp = 0;
	game->size_line = 0;
	game->endian = 0;
	game->north_texture.img = 0;
	game->south_texture.img = 0;
	game->west_texture.img = 0;
	game->east_texture.img = 0;
}
