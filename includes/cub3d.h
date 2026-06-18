/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:21:14 by pargev            #+#    #+#             */
/*   Updated: 2026/06/18 15:07:06 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/minilibx-linux/mlx.h"
# include "libft.h"
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
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
# define PLAYER_RADIUS 4
# define MOVE_SPEED 5

typedef enum direction
{
	North,
	South,
	West,
	East
}				t_direction;

typedef struct s_wall
{
	int			x;
	float		height;
	t_direction	direction;
	float		ray_x;
	float		ray_y;
}				t_wall;

typedef struct s_angles
{
	double		cos_a;
	double		sin_a;
}				t_angles;

typedef struct s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct s_point
{
	float		x;
	float		y;
}				t_point;

typedef struct s_segment
{
	t_point		p1;
	t_point		p2;
}				t_segment;

typedef struct s_ray
{
	int			quarter;
	int			side;
}				t_ray;

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
	int			x_position;
	int			y_position;
}				t_config;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct s_texture
{
	t_color		**img;
	int			width;
	int			height;
}				t_texture;

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			left_rotate;
	int			right_rotate;
	int			mouse_active;
	int			prev_mouse_x;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	t_player	*player;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_config	config;
	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	west_texture;
	t_texture	east_texture;
	t_direction	last_direction;
}				t_game;

// ========== Parsing ==========
t_config		parse(char *config_path);
void			cheack_config(t_config *config);
int				check_cell(char **map, int i, int j);
int				check_border(char **map, int i, int j);
int				is_player(char c);
void			parse_position(char **map, int *x_position, int *y_position);
int				parse_map_rows(char **config_text, char **map, int start);
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
void			free_all(t_game *game);
char			**ft_split2(char const *s, char *set);

// ========= render =========
void			init_player(t_player *player, t_config *config);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				mouse_press(int button, int x, int y, t_game *game);
int				mouse_release(int button, int x, int y, t_game *game);
int				mouse_move(int x, int y, t_game *game);
void			move_player(t_player *player, t_game *game);
int				close_window(t_game *game);
int				touch(float px, float py, t_game *game);
float			fixed_dist(t_point p1, t_point p2, t_game *game);
void			put_pixel(int x, int y, t_color color, t_game *game);
void			draw_square(t_pos p, int size, t_color color, t_game *game);
void			draw_map(t_game *game);
void			draw_ceiling_floor(t_game *game, int x, float height);
void			draw_walls(t_game *game, t_wall wall);
void			draw_line(t_player *player, t_game *game, float start_x, int i);
int				draw_loop(t_game *game);
void			init_game(t_game *game, t_config config);
char			**get_map(void);
int				is_wall(double x, double y, t_game *game);
void			set_coefficients(int quarter, int *px_c, int *py_c);
void			adjust_adjacent_xy(t_direction direction, int *x, int *y);
t_direction		get_new_direction(t_direction direction, int quarter);
void			lines_intersection_point(t_segment seg, t_point corner,
					t_ray ray, t_point *out);
t_texture		*get_texture(t_game *game, t_direction direction);
void			draw_square_side(t_pos p, int size, t_color color,
					t_game *game);
void			init_struct(t_game *game);
void			apply_movement(t_player *player, t_angles a, double *new_x,
					double *new_y);
void			resolve_ray(t_player *player, t_game *game, float angle,
					t_point *ray);
int				calculate_quarter(float angle);
int				near_angle(int quarter, t_segment seg, t_point *corner);
t_direction		wall_direction(int quarter, int side);
t_direction		check_adjacent(t_game *game, t_pos pos, t_direction direction,
					int quarter);
#endif