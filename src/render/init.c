/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:02:01 by zaleksan          #+#    #+#             */
/*   Updated: 2026/05/03 22:07:38 by pargev           ###   ########.fr       */
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

void	read_texture(t_game *game, char *path, t_texture *texture)
{
	t_image		img;
	int			i;
	int			j;

	img.img = mlx_xpm_file_to_image(game->mlx, path, &img.width, &img.height);
    if (!img.img)
	{
		free_all(game);
		exit_with_error(": loading image");
	}
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	
	texture->width = img.width;
	texture->height = img.height;
	
	texture->img = (t_color **)malloc(sizeof(t_color *) * (img.height + 1));
	i = 0;
	while (i < img.width)
	{
		texture->img[i] = (t_color *)malloc(sizeof(t_color) * (img.width + 1));
		j = 0;
		while (j < img.height)
		{
			texture->img[i][j] = get_img_pixel(&img, j, i);
			j++;
		}
		i++;
	}
	texture->img[i] = 0;
	mlx_destroy_image(game->mlx, img.img);
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


