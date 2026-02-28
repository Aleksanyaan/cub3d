/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:05:16 by zaleksan          #+#    #+#             */
/*   Updated: 2026/03/01 00:02:21 by pargev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(int x, int y, t_color color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color.blue;
	game->data[index + 1] = color.green;
	game->data[index + 2] = color.red;
}

void	draw_square(int x, int y, int size, t_color color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + size, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + size, color, game);
		i++;
	}
}

void	draw_map(t_game *game)
{
	char	**map;
	t_color		color;
	int		y;
	int		x;

	map = game->config.map;
	color = (t_color){0, 0, 255};
	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, color,
					game);
			x++;
		}
		y++;
	}
}

void	draw_line2(t_game *game, int x, float dist)
{
	float	height;
	int		y;
	int		wall_start;
	int		wall_end;

	height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	y = 0;
	wall_start = (HEIGHT - height) / 2;
	while (y < wall_start)
	{
		put_pixel(x, y, *game->config.ceiling_color, game);
		y++;
	}
	wall_end = wall_start + height;
	while (y < wall_end)
	{
		put_pixel(x, y, (t_color){0, 255, 0}, game);
		y++;
	}
	while (y < HEIGHT)
	{
		put_pixel(x, y, *game->config.floor_color, game);
		y++;
	}
}

void	draw_line(t_player *player, t_game *game, float start_x, int x)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, game))
	{
		// put_pixel(ray_x, ray_y, (t_color){255, 0, 0}, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	draw_line2(game, x, dist);
}

int	draw_loop(t_game *game)
{
	float		fraction;
	float		start_x;
	int			i;

	ft_bzero(game->data, HEIGHT * game->size_line);
	move_player(game->player, game);
	// draw_square(game->player->x, game->player->y, 15, (t_color){0, 255, 0}, game);
	// draw_map(game);
	fraction = PI / 3 / WIDTH;
	start_x = game->player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(game->player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
