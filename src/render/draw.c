/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:05:16 by zaleksan          #+#    #+#             */
/*   Updated: 2026/03/15 21:47:56 by pargev           ###   ########.fr       */
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

int	calculate_quarter(float angle)
{
	if (angle < 0)
		angle = 2 * PI + angle;
	else if (angle >= 2 * PI)
		angle = angle - 2 * PI;

	if (angle < PI/2)
		return (1);
	else if (angle < PI)
		return (2);
	else if (angle < 3 * PI / 2)
		return (3);
	return (4);
}

// calculates neearest recatangle paints coordinates and returns from what side of line is it
int	near_angle(int quarter, float start_x, float start_y, float end_x, float end_y, float *px, float *py)
{
	int		px_coefficent;
	int		py_coefficent;

	if (quarter == 1)
	{
		px_coefficent = 0;
		py_coefficent = 0;
	}
	else if (quarter == 2)
	{
		px_coefficent = 1;
		py_coefficent = 0;
	}
	else if (quarter == 3)
	{
		px_coefficent = 1;
		py_coefficent = 1;
	}
	else
	{
		px_coefficent = 0;
		py_coefficent = 1;
	}
	*px = ((int)(end_x / BLOCK_SIZE) + px_coefficent) * BLOCK_SIZE;
	*py = ((int)(end_y / BLOCK_SIZE) + py_coefficent) * BLOCK_SIZE;
	return ((end_x - start_x) * (*py - start_y) - (end_y - start_y) * (*px - start_x));
}

t_direction	wall_direction(int quarter, int side)
{
	t_direction directions[2];

	if (quarter == 1)
	{
		directions[0] = East;
		directions[1] = South;
	}
	else if (quarter == 2)
	{
		directions[0] = South;
		directions[1] = West;
	}
	else if (quarter == 3)
	{
		directions[0] = West;
		directions[1] = North;
	}
	else
	{
		directions[0] = North;
		directions[1] = East;
	}

	if (side < 0)
		return (directions[0]);
	return (directions[1]);
}

t_direction	check_adjacent(t_game *game, int x, int y, t_direction direction, int quarter)
{
	t_direction	new_direction;

	if (direction == North)
	{
		if (quarter == 3)
			new_direction = West;
		else
			new_direction = East;
		y++;
	}
	else if (direction == South)
	{
		if (quarter == 1)
			new_direction = East;
		else
			new_direction = West;
		y--;
	}
	else if (direction == West)
	{
		if (quarter == 2)
			new_direction = South;
		else
			new_direction = North;
		x++;
	}
	else
	{
		if (quarter == 1)
			new_direction = South;
		else
			new_direction = North;
		x--;
	}
	if (game->config.map[y][x] == '1')
		return (new_direction);
	return (direction);
}

void	lines_intersection_point(float x1, float y1, float x2, float y2,
								float px, float py, int quarter, int side,
								float *x, float *y)
{
	float		angle;
	float		dx;
	float		dy;
	float	u;
	float	den;

	angle = PI / 2;
	if (quarter == 1)
	{
		if (side >= 0)
			angle = 0;
	}
	else if (quarter == 2)
	{
		if (side < 0)
			angle = 0;
	}
	else if (quarter == 3)
	{
		if (side >= 0)
			angle = 0;
	}
	else
	{
		if (side < 0)
			angle = 0;
	}
	
	dx = cos(angle);
	dy = sin(angle);
	den = den = (x2 - x1) * dy - (y2 - y1) * dx;
	// printf("x1 %f y1 %f x2 %f y2 %f px %f py %f den %f quarter %d angle %f\n", x1, y1, x2, y2, px, py, den, quarter, angle);
	u = ((px - x1) * dy - (py - y1) * dx) / den;

    *x = x1 + u * (x2 - x1);
    *y = y1 + u * (y2 - y1);
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

void	draw_line(t_player *player, t_game *game, float angle, int x)
{
	float		cos_angle;
	float		sin_angle;
	float		ray_x;
	float		ray_y;
	float		dist;
	int			angle_side;
	float		px;
	float		py;
	int			quarter;
	t_direction direction;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, game))
	{
		// put_pixel(ray_x, ray_y, (t_color){255, 0, 0}, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	quarter = calculate_quarter(angle);
	angle_side = near_angle(quarter, player->x, player->y, ray_x, ray_y, &px, &py);
	direction = wall_direction(quarter, angle_side);
	direction = check_adjacent(game, ray_x / BLOCK_SIZE, ray_y / BLOCK_SIZE, direction, quarter);
	// printf("%f %f | ", ray_x, ray_y);
	lines_intersection_point(player->x, player->y, ray_x, ray_y, px, py, quarter, angle_side, &ray_x, &ray_y);
	// printf("%f %f\n", ray_x, ray_y);
	t_color color;
	if (direction == North)
		color = (t_color){255, 0, 0};
	else if (direction == South)
		color = (t_color){0, 255, 0};
	else if (direction == West)
		color = (t_color){0, 0, 255};
	else
		color = (t_color){255, 255, 0};
	// draw_square(ray_x, ray_y, 10, color, game);
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
	draw_fps(game, &last_time, &frames);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
