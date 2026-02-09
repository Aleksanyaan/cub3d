/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:02:01 by zaleksan          #+#    #+#             */
/*   Updated: 2026/02/07 18:59:09 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_game *game)
{
	if (!game)
		exit(1);
	cleanup(game);
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

// int	init_game(t_game *game)
// {
// 	init_struct(game);
// 	game->player = malloc(sizeof(t_player));
// 	if (!game->player)
// 		return (1);
// 	init_player(game->player);
// 	game->map = get_map();
// 	if (!game->map)
// 		return (1);
// 	game->mlx = mlx_init();
// 	if (!game->mlx)
// 		return (1);
// 	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cube3D");
// 	if (!game->win)
// 		return (cleanup(game), 1);
// 	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
// 	if (!game->img)
// 		return (cleanup(game), 1);
// 	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
// 			&game->endian);
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// 	return (0);
// }

int init_game(t_game *game)
{
     // set all pointers to NULL

    // allocate player
    game->player = malloc(sizeof(t_player));
    if (!game->player)
    {
        free_all(game);
		exit(1);
    }
    init_struct(game);
    init_player(game->player);

    // load map
    game->map = get_map();
    if (!game->map)
        return (1);

    // initialize MLX
    game->mlx = mlx_init();
    if (!game->mlx)
        return (1);

    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cube3D");
    if (!game->win)
        return (cleanup(game), 1);

    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img)
        return (cleanup(game), 1);

    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
                                   &game->endian);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    return (0);
}


