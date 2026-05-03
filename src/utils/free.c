/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:21:05 by pargev            #+#    #+#             */
/*   Updated: 2026/05/03 13:48:19 by pargev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_string_array(char **string)
{
	int	i;

	i = 0;
	if (string)
	{
		while (string[i])
		{
			free(string[i]);
			i++;
		}
		free(string);
	}
}

void	free_config(t_config *config)
{
	if (config->north_texture)
		free(config->north_texture);
	if (config->south_texture)
		free(config->south_texture);
	if (config->west_texture)
		free(config->west_texture);
	if (config->east_texture)
		free(config->east_texture);
	if (config->floor_color)
		free(config->floor_color);
	if (config->ceiling_color)
		free(config->ceiling_color);
	if (config->map)
		free_string_array(config->map);
}

void	free_img(t_color **img)
{
	int	i;
	
	if (img)
	{
		i = 0;
		while (img[i])
		{
			if (!img[i])
				break ;
			free (img[i]);
			i++;
		}
		free(img);
	}
}

void	free_textures(t_game *game)
{
	if (game->north_texture.img)
		free_img(game->north_texture.img);
	if (game->south_texture.img)
		free_img(game->south_texture.img);
	if (game->west_texture.img)
		free_img(game->west_texture.img);
	if (game->east_texture.img)
		free_img(game->east_texture.img);
}

void	free_all(t_game *game)
{
	if (!game)
		return ;
	free_textures(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	if (game->player)
		free(game->player);
	free_config(&game->config);
	free(game);
}