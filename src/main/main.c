/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:21:10 by pargev            #+#    #+#             */
/*   Updated: 2026/01/30 15:39:37 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_config	config;
	t_game		game;
	// int			i;

	// config = parse("/home/pargev/Desktop/cub3d/config.cub");
	// printf("%s\n", config.north_texture);
	// printf("%s\n", config.south_texture);
	// printf("%s\n", config.west_texture);
	// printf("%s\n", config.east_texture);
	// printf("%d,%d,%d\n", config.floor_color->red, config.floor_color->green,
	// 	config.floor_color->blue);
	// printf("%d,%d,%d\n", config.ceiling_color->red, config.ceiling_color->green,
	// 	config.ceiling_color->blue);
	// i = 0;
	// while (config.map && config.map[i])
	// {
	// 	printf("%s\n", config.map[i]);
	// 	i++;
	// }
	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	free_config(&config);
}
