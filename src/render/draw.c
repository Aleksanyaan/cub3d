#include "../includes/cub3d.h"

void put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_game *game)
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
	int		color;
	int		y;
	int		x;

	map = game->map;
	color = 0x0000FF;
	x = 0;
	y = 0;
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if(map[y][x] == '1')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, color, game);
			x++;
		}
		y++;
	}
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	float	ray_x = player->x;
	float	ray_y = player->y;

	while(!touch(ray_x, ray_y, game))
	{
		// put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	float	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	float	height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	int		start_y = (HEIGHT - height) / 2;
	int		end = start_y + height;

	while(start_y < end)
	{
		put_pixel(i, start_y, 0x00FF00, game);
		start_y++;
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = &game->player;
	ft_bzero(game->data, HEIGHT * game->size_line);
	move_player(player);
	// draw_square(player->x, player->y, 15, 0x00FF00, game);
	// draw_map(game);

	float	fraction = PI / 3 / WIDTH;
	float	start_x = player->angle - PI / 6;
	int		i = 0;
	while(i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
