/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:51:34 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 14:54:56 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:58:45 by zaleksan          #+#    #+#             */
/*   Updated: 2026/05/03 22:13:04 by pargev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_press(int button, int x, int y, t_game *game)
{
	(void)y;
	if (button == 1)
	{
		game->player->mouse_active = 1;
		game->player->prev_mouse_x = x;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		game->player->mouse_active = 0;
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	int		delta_x;
	float	sensitivity;

	(void)y;
	if (!game->player->mouse_active)
		return (0);
	sensitivity = 0.005;
	delta_x = x - game->player->prev_mouse_x;
	game->player->prev_mouse_x = x;
	game->player->angle += delta_x * sensitivity;
	if (game->player->angle > 2 * PI)
		game->player->angle -= 2 * PI;
	if (game->player->angle < 0)
		game->player->angle += 2 * PI;
	return (0);
}

void	apply_movement(t_player *player, t_angles a,
				double *new_x, double *new_y)
{
	if (player->key_up)
	{
		*new_x += a.cos_a * MOVE_SPEED;
		*new_y += a.sin_a * MOVE_SPEED;
	}
	if (player->key_down)
	{
		*new_x -= a.cos_a * MOVE_SPEED;
		*new_y -= a.sin_a * MOVE_SPEED;
	}
	if (player->key_right)
	{
		*new_x += -a.sin_a * MOVE_SPEED;
		*new_y += a.cos_a * MOVE_SPEED;
	}
	if (player->key_left)
	{
		*new_x += a.sin_a * MOVE_SPEED;
		*new_y += -a.cos_a * MOVE_SPEED;
	}
}
