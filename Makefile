CC			=	cc
FLAGS		=	-g -Wall -Wextra -Werror

OBJ_DIR		=	src/obj
INCLUDES	=	includes
LIBFT_DIR	=	libs/libft
MLX_DIR		=	libs/minilibx-linux

LIBFT_A		=	$(LIBFT_DIR)/libft.a
MLX_A		=	$(MLX_DIR)/libmlx.a

MAIN		=	main.c
PARSING		=	parse.c parse_color.c check_config.c check_config_utils.c parse_utils.c read_file.c
UTILS		=	free.c ft_str.c exit.c ft_split2.c
RENDER		=	distance.c draw.c init.c player.c collision.c mouse.c init_utils.c draw_utils.c draw_utils2.c draw_line.c draw_fps.c

NAME		=	cub3d

HEADERS		=	$(INCLUDES)/cub3d.h

SRC			=	$(addprefix src/main/, $(MAIN)) \
				$(addprefix src/parsing/, $(PARSING)) \
				$(addprefix src/utils/, $(UTILS)) \
				$(addprefix src/render/, $(RENDER))

OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:src/%.c=%.o))

LIBFT		=	-L./$(LIBFT_DIR) -lft
MLX			=	-L./$(MLX_DIR) -lmlx -lXext -lX11 -lm
IFLAGS		=	-I./$(INCLUDES) -I./$(LIBFT_DIR) -I./$(MLX_DIR)

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT_A):
	@make -s -C $(LIBFT_DIR)

$(MLX_A):
	@make -s -C $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)
	@make -s -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re lib build minilibx
