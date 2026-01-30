/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:21:14 by pargev            #+#    #+#             */
/*   Updated: 2026/01/30 15:55:47 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define PI 3.14159265358979
# define BLOCK_SIZE 64
# define LEFT 65361
# define RIGHT 65363

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	t_color		*floor_color;
	t_color		*ceiling_color;
	char		**map;
}				t_config;

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;

	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;

	int		left_rotate;
	int		right_rotate;

}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	t_player	player;

	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	char		**map;
}				t_game;

// ========== Parsing ==========
t_config		parse(char *config_path);
void			cheack_config(t_config *config);
int				check_file_extension(char *path, char *extension);
t_color			*parse_color(char *color_text);
char			**read_config(char *path);

// ========= utils =========
void			exit_with_error(char *error_message);
void			free_and_exit(t_config *config, char **string,
					char *error_message);
void			free_string_array(char **string);
void			free_config(t_config *config);
int				ft_str_only(const char *s, const char *allowed);
char			*ft_strdup_free(char *s1);

// ========= render =========
void			init_player(t_player *player);
int				key_press(int keycode, t_player *player);
int				key_release(int keycode, t_player *player);
void			move_player(t_player *player);
int				close_window(void);
int				touch(float px, float py, t_game *game);
float			fixed_dist(float x1, float y1, float x2, float y2,
					t_game *game);
void			put_pixel(int x, int y, int color, t_game *game);
void			draw_square(int x, int y, int size, int color, t_game *game);
void			draw_map(t_game *game);
void			draw_line(t_player *player, t_game *game, float start_x, int i);
int				draw_loop(t_game *game);
void			init_game(t_game *game);
char			**get_map(void);

#endif