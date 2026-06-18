/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:06:38 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 14:45:28 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_ray(t_player *player, t_game *game, float angle, t_point *ray)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	ray->x = player->x;
	ray->y = player->y;
	while (!touch(ray->x, ray->y, game))
	{
		ray->x += cos_angle;
		ray->y += sin_angle;
	}
}

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	draw_fps(t_game *game, long *last_time, int *frames)
{
	long	now_time;
	char	*fps_str;

	(void)game;
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

void	resolve_ray(t_player *player, t_game *game, float angle, t_point *ray)
{
	t_segment	seg;
	t_point		corner;
	t_ray		r;
	t_direction	direction;

	cast_ray(player, game, angle, ray);
	r.quarter = calculate_quarter(angle);
	seg = (t_segment){{player->x, player->y}, {ray->x, ray->y}};
	r.side = near_angle(r.quarter, seg, &corner);
	direction = wall_direction(r.quarter, r.side);
	direction = check_adjacent(game, (t_pos){ray->x / BLOCK_SIZE,
			ray->y / BLOCK_SIZE}, direction, r.quarter);
	lines_intersection_point(seg, corner, r, ray);
	game->last_direction = direction;
}
