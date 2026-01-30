#include "../includes/cub3d.h"

int	close_window()
{
	exit(0);
}

char **get_map(void)
{
	static char *map[] = {
		"11111111111111111111",
		"10000000000000000001",
		"10111111111111111001",
		"10000000000000001001",
		"10001100000000001001",
		"100010000P0000100001",
		"10001110000000001001",
		"10000000000000001001",
		"10000000000001000001",
		"10000000000000000001",
		"11111111111111111111",
		NULL
	};

	return (map);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cube3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}