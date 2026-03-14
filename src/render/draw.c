/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:05:16 by zaleksan          #+#    #+#             */
/*   Updated: 2026/03/15 00:57:03 by pargev           ###   ########.fr       */
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

t_direction	all_direction(float angle, double px, double py)
{
	double			x;
	double			y;
	double		error;
	t_direction directions[2];

	// need change operator to math function
	x = fmod(px, BLOCK_SIZE);
	y = fmod(py, BLOCK_SIZE);
	
	// printf("angle = %f x = %f, y = %f\n", angle, x, y);
	error = PI / 6;
	
	if (angle >= 0)
	{
		if (angle < PI/2)
		{
			if (x > y)
				return (South);
			else
				return (East);
		}
		else if (angle < PI)
		{
			if (y > (double)BLOCK_SIZE - x)
				return (West);
			else
				return (South);
		}
		else if (angle < 3 * PI / 2)
		{
			if ((double)BLOCK_SIZE - x > (double)BLOCK_SIZE - y)
				return (North);
			else
				return (West);
		}
		else
		{
			if (x < (double)BLOCK_SIZE - y)
				return (East);
			else
				return (North);
		}
	}
	else
	{
		if (x < (double)BLOCK_SIZE - y)
			return (East);
		else
			return (North);
	}

	if (y == 0 || y == BLOCK_SIZE - 1)
		return (directions[0]);
	return (directions[1]);
}


void	draw_line2(t_game *game, int x, float dist, t_color color)
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
	y = wall_start;
	while (y < wall_end)
	{
		put_pixel(x, y, color, game);
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
	float		cos_angle;
	float		sin_angle;
	float		ray_x;
	float		ray_y;
	float		dist;
	t_direction direction;

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
	direction = all_direction(start_x, ray_x, ray_y);
	t_color color;
	if (direction == North)
		color = (t_color){255, 0, 0};
	else if (direction == South)
		color = (t_color){0, 255, 0};
	else if (direction == West)
		color = (t_color){0, 0, 255};
	else
		color = (t_color){255, 255, 0};
	// put_pixel(ray_x, ray_y, color, game);
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	draw_line2(game, x, dist, color);
}

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	draw_fps(t_game *game, long *last_time, int *frames)
{
	long	now_time;
	char	*fps_str;

	now_time = current_time_ms();
	(*frames)++;
	if (now_time - *last_time >= 1000)
	{
		fps_str = ft_itoa(*frames);
		printf("FPS = %s\n", fps_str);
		free(fps_str);
		*frames = 0;
		*last_time = now_time;
	}
}

int	draw_loop(t_game *game)
{
	static long	last_time = 0;
    static int	frames = 0;
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
	// draw_fps(game, &last_time, &frames);
	// for (int i = 0; i < 10000000; i++);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
