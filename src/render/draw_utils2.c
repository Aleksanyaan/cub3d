/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:22:12 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 15:02:03 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(int x, int y, t_color color, t_game *game)
{
	int	index;

	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color.blue;
	game->data[index + 1] = color.green;
	game->data[index + 2] = color.red;
}

void	draw_square_side(t_pos p, int size, t_color color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
		put_pixel(p.x + i++, p.y, color, game);
	i = 0;
	while (i < size)
		put_pixel(p.x, p.y + i++, color, game);
}
