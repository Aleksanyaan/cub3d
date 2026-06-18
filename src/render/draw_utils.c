/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:57:34 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 14:28:58 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_coefficients(int quarter, int *px_c, int *py_c)
{
	if (quarter == 1)
	{
		*px_c = 0;
		*py_c = 0;
	}
	else if (quarter == 2)
	{
		*px_c = 1;
		*py_c = 0;
	}
	else if (quarter == 3)
	{
		*px_c = 1;
		*py_c = 1;
	}
	else
	{
		*px_c = 0;
		*py_c = 1;
	}
}

void	adjust_adjacent_xy(t_direction direction, int *x, int *y)
{
	if (direction == North)
		(*y)++;
	else if (direction == South)
		(*y)--;
	else if (direction == West)
		(*x)++;
	else if (direction == East)
		(*x)--;
}

t_direction	get_new_direction(t_direction direction, int quarter)
{
	if ((direction == West && quarter == 3)
		|| (direction == East && quarter == 4))
		return (North);
	if ((direction == West && quarter == 2)
		|| (direction == East && quarter == 1))
		return (South);
	if ((direction == North && quarter == 3)
		|| (direction == South && quarter == 2))
		return (West);
	if ((direction == North && quarter == 4)
		|| (direction == South && quarter == 1))
		return (East);
	return (direction);
}

void	lines_intersection_point(t_segment seg, t_point corner,
			t_ray ray, t_point *out)
{
	float	angle;
	float	dx;
	float	dy;
	float	u;
	float	den;

	angle = PI / 2;
	if ((ray.quarter == 1 && ray.side >= 0)
		|| (ray.quarter == 2 && ray.side < 0)
		|| (ray.quarter == 3 && ray.side >= 0)
		|| (ray.quarter == 4 && ray.side < 0))
		angle = 0;
	dx = cos(angle);
	dy = sin(angle);
	den = (seg.p2.x - seg.p1.x) * dy - (seg.p2.y - seg.p1.y) * dx;
	u = ((corner.x - seg.p1.x) * dy - (corner.y - seg.p1.y) * dx) / den;
	out->x = seg.p1.x + u * (seg.p2.x - seg.p1.x);
	out->y = seg.p1.y + u * (seg.p2.y - seg.p1.y);
}

t_texture	*get_texture(t_game *game, t_direction direction)
{
	if (direction == North)
		return (&game->north_texture);
	if (direction == South)
		return (&game->south_texture);
	if (direction == West)
		return (&game->west_texture);
	return (&game->east_texture);
}
