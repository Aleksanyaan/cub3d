/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:02:01 by zaleksan          #+#    #+#             */
/*   Updated: 2026/03/17 23:14:15 by pargev           ###   ########.fr       */
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
	game->north_texture.img = NULL;
	game->south_texture.img = NULL;
	game->west_texture.img = NULL;
	game->east_texture.img = NULL;
	game->bpp = 0;
	game->size_line = 0;
	game->endian = 0;
}

void	read_texture(t_game *game)
{
	t_texture	*north;
	t_texture	*south;
	t_texture	*west;
	t_texture	*east;

	north = &game->north_texture;
	south = &game->south_texture;
	west = &game->west_texture;
	east = &game->east_texture;
	north->img = mlx_xpm_file_to_image(game->mlx, game->config.north_texture, &north->width, &north->height);
	south->img = mlx_xpm_file_to_image(game->mlx, game->config.south_texture, &south->width, &south->height);
	west->img = mlx_xpm_file_to_image(game->mlx, game->config.west_texture, &west->width, &west->height);
	east->img = mlx_xpm_file_to_image(game->mlx, game->config.east_texture, &east->width, &east->height);
    if (!north->img || !south->img || !west->img || !east->img)
	{
		free_all(game);
		exit_with_error(": loading image\n");
	}
	north->addr = mlx_get_data_addr(north->img, &north->bpp, &north->line_len, &north->endian);
	south->addr = mlx_get_data_addr(south->img, &south->bpp, &south->line_len, &south->endian);
	west->addr = mlx_get_data_addr(west->img, &west->bpp, &west->line_len, &west->endian);
	east->addr = mlx_get_data_addr(east->img, &east->bpp, &east->line_len, &east->endian);
}

void	init_game(t_game *game, t_config config)
{
	game->config = config;
	init_struct(game);
 	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		free_all(game);
		exit(1);
	}
	init_player(game->player);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_all(game);
		exit(1);
	}
	read_texture(game);
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


