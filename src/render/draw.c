/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:50:51 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 14:22:08 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square(t_pos p, int size, t_color color, t_game *game)
{
	int	i;

	draw_square_side(p, size, color, game);
	i = 0;
	while (i < size)
		put_pixel(p.x + size, p.y + i++, color, game);
	i = 0;
	while (i < size)
		put_pixel(p.x + i++, p.y + size, color, game);
}

void	draw_map(t_game *game)
{
	char	**map;
	t_color	color;
	int		y;
	int		x;

	map = game->config.map;
	color = (t_color){0, 0, 255};
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square((t_pos){x * BLOCK_SIZE, y * BLOCK_SIZE}, BLOCK_SIZE,
					color, game);
			x++;
		}
		y++;
	}
}

void	draw_ceiling_floor(t_game *game, int x, float height)
{
	int	y;
	int	wall_start;

	y = 0;
	wall_start = (HEIGHT - height) / 2;
	if (wall_start > HEIGHT)
		wall_start = HEIGHT;
	while (y < wall_start)
		put_pixel(x, y++, *game->config.ceiling_color, game);
	y = wall_start + height;
	if (y < 0)
		y = 0;
	while (y < HEIGHT)
		put_pixel(x, y++, *game->config.floor_color, game);
}

static void	draw_wall_pixels(t_game *game, t_wall wall, t_texture *texture)
{
	float	x_coefficient;
	float	y_coefficient;
	int		wall_start;
	int		wall_end;
	int		y;

	if (wall.direction == North || wall.direction == South)
		x_coefficient = fmod(wall.ray_x, BLOCK_SIZE) / BLOCK_SIZE;
	else
		x_coefficient = fmod(wall.ray_y, BLOCK_SIZE) / BLOCK_SIZE;
	wall_start = (HEIGHT - wall.height) / 2;
	wall_end = wall_start + wall.height;
	y = 0;
	if (wall_start > 0)
		y = wall_start;
	if (wall_end > HEIGHT)
		wall_end = HEIGHT;
	while (y < wall_end)
	{
		y_coefficient = (y - wall_start) / wall.height;
		put_pixel(wall.x, y++, texture->img[(int)(texture->height
				* y_coefficient)][(int)(texture->width * x_coefficient)], game);
	}
}

void	draw_walls(t_game *game, t_wall wall)
{
	draw_wall_pixels(game, wall, get_texture(game, wall.direction));
}
