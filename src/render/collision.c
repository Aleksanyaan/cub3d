#include "../includes/cub3d.h"

int	is_wall(double x, double y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BLOCK_SIZE);
	map_y = (int)(y / BLOCK_SIZE);
	if (map_y < 0 || !game->map[map_y])
		return (1);
	if (map_x < 0 || game->map[map_y][map_x] == '\0')
		return (1);
	return (game->map[map_y][map_x] == '1');
}

