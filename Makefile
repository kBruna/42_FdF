COLOR_BLUE	= \033[0;34
COLOR_GREEN	= \033[0;32
COLOR_RED	= \033[0;31
COLOR_END	= \033[0m

NAME        = fdf
CC          = cc
CFLAGS		= -Wall -Wextra -Werror -g3
CFLAGS     += -Iincludes -Iminilibx -I. -Isrc/Libft/includes

SRCS        = $(shell find src -name "*.c")
DIR_LIBFT   = src/Libft

MLX_DIR     = minilibx-linux
MLX_LIB 	= $(MLX_DIR)/libmlx.a

MLX_FLAGS   = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(SRCS) $(MLX_LIB)
	@echo "\n$(COLOR_GREEN);1m	-> Compiling files...$(COLOR_END)\n"
	$(CC) $(CFLAGS) $(SRCS) $(MLX_FLAGS) -o $(NAME)
	@echo "\n$(COLOR_GREEN);1m	-> $(NAME) compiled successfully!$(COLOR_END)"
	@echo "\n$(COLOR_GREEN);1m	-> Compilation complete!$(COLOR_END)\n"

$(MLX_LIB):
	@echo "$(COLOR_GREEN);1m	-> Building MiniLibX...$(COLOR_END)\n"
	@make -sC $(MLX_DIR)

clean:
	@make -sC $(DIR_LIBFT) clean
	@echo "$(COLOR_RED);1m	-> Removing MinilibX files...$(COLOR_END)\n"
	@make -sC $(MLX_DIR) clean
	@echo "\n$(COLOR_BLUE);1m	-> Clean complete.$(COLOR_END)\n"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR_RED);1m	-> Deleting executable file...$(COLOR_END)"
	@echo "\n$(COLOR_BLUE);1m	-> Delete files complete.$(COLOR_END)\n"

re: fclean all

.PHONY: all clean fclean re
