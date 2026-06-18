/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:51:13 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 14:55:02 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player, t_config *config)
{
	player->x = BLOCK_SIZE * config->x_position + BLOCK_SIZE / 2;
	player->y = BLOCK_SIZE * config->y_position + BLOCK_SIZE / 2;
	if (config->map[config->y_position][config->x_position] == 'N')
		player->angle = 3 * PI / 2;
	else if (config->map[config->y_position][config->x_position] == 'S')
		player->angle = PI / 2;
	else if (config->map[config->y_position][config->x_position] == 'W')
		player->angle = PI;
	else
		player->angle = 0;
	player->key_up = 0;
	player->key_down = 0;
	player->key_left = 0;
	player->key_right = 0;
	player->left_rotate = 0;
	player->right_rotate = 0;
	player->mouse_active = 0;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == W)
		game->player->key_up = 1;
	if (keycode == A)
		game->player->key_left = 1;
	if (keycode == S)
		game->player->key_down = 1;
	if (keycode == D)
		game->player->key_right = 1;
	if (keycode == LEFT)
		game->player->left_rotate = 1;
	if (keycode == RIGHT)
		game->player->right_rotate = 1;
	if (keycode == ESC)
		close_window(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->player->key_up = 0;
	if (keycode == A)
		game->player->key_left = 0;
	if (keycode == S)
		game->player->key_down = 0;
	if (keycode == D)
		game->player->key_right = 0;
	if (keycode == LEFT)
		game->player->left_rotate = 0;
	if (keycode == RIGHT)
		game->player->right_rotate = 0;
	return (0);
}

void	rotate_palyer(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.04;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

void	move_player(t_player *player, t_game *game)
{
	double		new_x;
	double		new_y;
	t_angles	a;

	rotate_palyer(player);
	a.cos_a = cos(player->angle);
	a.sin_a = sin(player->angle);
	new_x = player->x;
	new_y = player->y;
	apply_movement(player, a, &new_x, &new_y);
	if (!is_wall(new_x + PLAYER_RADIUS, player->y, game)
		&& !is_wall(new_x - PLAYER_RADIUS, player->y, game))
		player->x = new_x;
	if (!is_wall(player->x, new_y + PLAYER_RADIUS, game)
		&& !is_wall(player->x, new_y - PLAYER_RADIUS, game))
		player->y = new_y;
}
