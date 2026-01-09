NAME		= cub3d

LIBFT_DIR	= libs/libft

LIBFT		= -L./$(LIBFT_DIR) -lft

MLX_DIR		= libs/minilibx-linux

MLX			= -L./$(MLX_DIR) -lmlx -lm -lX11 -lXext

INCLUDES	= -I./includes -I./$(LIBFT_DIR) -I./$(MLX_DIR)

HEADER		= ./includes/cub3d.h

CC			= cc

FLAGS		= -Wall -Wextra -Werror

SRC_DIR		= ./src

SRC			= ${SRC_DIR}/main.c

OBJ			= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

BUILD_DIR	= ./build

all: build lib minilibx $(NAME)

$(BUILD_DIR)/%.o:	$(SRC_DIR)/%.c Makefile $(HEADER)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a Makefile
	$(CC) $(FLAGS) $(INCLUDES) $(OBJ) -o $(NAME) $(LIBFT) $(MLX)

lib:
	make -C $(LIBFT_DIR)

minilibx:
	make -C $(MLX_DIR)

build:
	mkdir -p ${BUILD_DIR}

clean:
	rm -rf $(BUILD_DIR)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY:	all fclean clean re lib build minilibx