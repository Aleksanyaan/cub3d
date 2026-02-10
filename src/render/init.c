/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:02:01 by zaleksan          #+#    #+#             */
/*   Updated: 2026/02/10 20:50:30 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_game *game)
{
	if (!game)
		exit(1);
	cleanup(game);
    // free_map(game->map);
	free_all(game);
	exit(0);
}

char	**get_map(void)
{
	static char	*map[] = {"11111111111111111111", "10000000000000000001",
			"10111111111111111001", "10000000000000001001",
			"10001100000000001001", "100010000P0000100001",
			"10001110000000001001", "10000000000000001001",
			"10000000000001000001", "10000000000000000001",
			"11111111111111111111", NULL};

	return (map);
}

void	init_struct(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->data = NULL;
	game->map = NULL;
	game->bpp = 0;
	game->size_line = 0;
	game->endian = 0;
}

void init_game(t_game *game)
{
 	game->player = malloc(sizeof(t_player));
	if (!game->player)
		exit(1);
	init_player(game->player);
    init_struct(game);
	game->map = get_map();
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_all(game);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cube3D");
	if (!game->win)
	{
		free_all(game);
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		free_all(game);
		exit(1);
	}
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!game->data)
	{
		free_all(game);
		exit(1);
	}
}


