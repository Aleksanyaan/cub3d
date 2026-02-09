#include "../includes/cub3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	free_all(t_game *game)
{
	if (!game)
		exit(1);
	free(game->map);
	free(game->player);
	free(game);
}

void	cleanup(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}