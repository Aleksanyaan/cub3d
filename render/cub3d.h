#ifndef CUB3D_H
#define CUB3D_H

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

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

typedef struct s_player
{
    float   x;
    float   y;
    float   angle;

    bool    key_up;
    bool    key_down;
    bool    key_left;
    bool    key_right;

    bool    left_rotate;
    bool    right_rotate;

}   t_player;

typedef struct  s_game
{
    void *mlx;
    void *win;
    void *img;
    t_player player;

    char    *data;
    int     bpp;
    int     size_line;
    int     endian;
    char    **map;
}   t_game;



void    init_player(t_player *player);
int     key_press(int keycode, t_player *player);
int     key_release(int keycode, t_player *player);
void    move_player(t_player *player);

int	close_window();

#endif