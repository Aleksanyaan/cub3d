/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:21:33 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 13:23:16 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char	**argv)
{
	t_config	config;
	t_game		*game;

	if (argc != 2)
		return (1);
	config = parse(argv[1]);
	printf("%s\n", config.north_texture);
	printf("%s\n", config.south_texture);
	printf("%s\n", config.west_texture);
	printf("%s\n", config.east_texture);
	game = malloc(sizeof(t_game));
	if (!game)
		free_and_exit(&config, NULL, "");
	init_game(game, config);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_press, game);
	mlx_hook(game->win, 5, 1L << 3, mouse_release, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
	free_all(game);
}
