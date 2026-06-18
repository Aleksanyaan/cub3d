/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:02:30 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 14:39:52 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	calculate_quarter(float angle)
{
	if (angle < 0)
		angle = 2 * PI + angle;
	else if (angle >= 2 * PI)
		angle = angle - 2 * PI;
	if (angle < PI / 2)
		return (1);
	else if (angle < PI)
		return (2);
	else if (angle < 3 * PI / 2)
		return (3);
	return (4);
}

int	near_angle(int quarter, t_segment seg, t_point *corner)
{
	int	px_coefficent;
	int	py_coefficent;

	set_coefficients(quarter, &px_coefficent, &py_coefficent);
	corner->x = ((int)(seg.p2.x / BLOCK_SIZE) + px_coefficent) * BLOCK_SIZE;
	corner->y = ((int)(seg.p2.y / BLOCK_SIZE) + py_coefficent) * BLOCK_SIZE;
	return ((seg.p2.x - seg.p1.x) * (corner->y - seg.p1.y)
		- (seg.p2.y - seg.p1.y) * (corner->x - seg.p1.x));
}

t_direction	wall_direction(int quarter, int side)
{
	t_direction	directions[2];

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

t_direction	check_adjacent(t_game *game, t_pos pos,
				t_direction direction, int quarter)
{
	t_direction	new_direction;

	new_direction = get_new_direction(direction, quarter);
	adjust_adjacent_xy(direction, &pos.x, &pos.y);
	if (game->config.map[pos.y][pos.x] == '1')
		return (new_direction);
	return (direction);
}

void	draw_line(t_player *player, t_game *game, float angle, int x)
{
	t_point	ray;
	t_point	player_pos;
	float	dist;
	int		height;

	resolve_ray(player, game, angle, &ray);
	player_pos = (t_point){player->x, player->y};
	dist = fixed_dist(player_pos, ray, game);
	height = (BLOCK_SIZE / dist) * (WIDTH / 1.2);
	draw_ceiling_floor(game, x, height);
	draw_walls(game, (t_wall){x, height, game->last_direction,
		ray.x, ray.y});
}
