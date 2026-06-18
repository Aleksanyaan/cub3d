/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:02:01 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 14:47:49 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_color	get_img_pixel(t_image *img, int x, int y)
{
	t_color	color_rgb;
	int		color_hex;

	color_hex = *(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8)));
	color_rgb.blue = (color_hex >> 16) & 0xFF;
	color_rgb.green = (color_hex >> 8) & 0xFF;
	color_rgb.red = color_hex & 0xFF;
	return (color_rgb);
}

static void	fill_texture(t_image *img, t_texture *texture)
{
	int	i;
	int	j;

	texture->img = (t_color **)malloc(sizeof(t_color *) * (img->height + 1));
	i = 0;
	while (i < img->width)
	{
		texture->img[i] = (t_color *)malloc(sizeof(t_color) * (img->width + 1));
		j = 0;
		while (j < img->height)
		{
			texture->img[i][j] = get_img_pixel(img, j, i);
			j++;
		}
		i++;
	}
	texture->img[i] = 0;
}

void	read_texture(t_game *game, char *path, t_texture *texture)
{
	t_image	img;

	img.img = mlx_xpm_file_to_image(game->mlx, path,
			&img.width, &img.height);
	if (!img.img)
	{
		free_all(game);
		exit_with_error(": loading image");
	}
	img.addr = mlx_get_data_addr(img.img, &img.bpp,
			&img.line_len, &img.endian);
	texture->width = img.width;
	texture->height = img.height;
	fill_texture(&img, texture);
	mlx_destroy_image(game->mlx, img.img);
}

static void	init_window_and_image(t_game *game)
{
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
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
	{
		free_all(game);
		exit(1);
	}
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
	init_player(game->player, &game->config);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_all(game);
		exit(1);
	}
	read_texture(game, game->config.north_texture, &game->north_texture);
	read_texture(game, game->config.west_texture, &game->west_texture);
	read_texture(game, game->config.south_texture, &game->south_texture);
	read_texture(game, game->config.east_texture, &game->east_texture);
	init_window_and_image(game);
}
