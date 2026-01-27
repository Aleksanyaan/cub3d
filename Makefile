CC			=	cc
FLAGS		=	-fsanitize=address -g #-Wall -Wextra -Werror

OBJ_DIR		=	src/obj
INCLUDES	=	includes/
LIBFT_DIR	=	libs/libft
MLX_DIR		=	libs/minilibx-linux

LIBFT_A		=	$(LIBFT)libft.a
MLX_A		=	$(MLX_DIR)/libmlx.a

MAIN		=	main.c exit.c
PARSING		=	parse.c
UTILS		=	free.c ft_str.c

NAME		=	cub3d

HEADERS		=	${INCLUDES}/cub3d.h
SRC			=	$(addprefix src/main/, $(MAIN)) \
				$(addprefix src/parsing/, $(PARSING)) \
				$(addprefix src/utils/, $(UTILS))
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:src/%.c=%.o))

LIBFT		=	-L./$(LIBFT_DIR) -lft
MLX			=	-L./$(MLX_DIR) -lmlx -lm -lX11 -lXext
IFLAGS		=	-I./$(INCLUDES) -I./$(LIBFT_DIR) #-I./$(MLX_DIR)

SRC_DIR		= ./src

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c ${HEADERS}
				@mkdir -p $(dir $@)
				${CC} ${FLAGS} ${IFLAGS} -c $< -o $@

$(NAME): 		$(OBJ) $(LIBFT_A) Makefile
				$(CC) $(FLAGS) $(OBJ) $(IFLAGS) $(LIBFT) -o $(NAME)

${LIBFT_A}:
				@make -s -C $(LIBFT_DIR)

${MLX_A}:
				@make -s -C $(MLX_DIR)

clean:
				rm -rf ${OBJ_DIR}
				@make -s -C $(LIBFT_DIR) fclean

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all fclean clean re lib build minilibx