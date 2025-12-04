NAME        = fdf

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
CFLAGS     += -Iincludes -Iminilibx -I. -Isrc/Libft/includes

SRCS        = $(shell find src -name "*.c")
//SRCS       += $(shell find includes/ft_printf -name "*.c")

OBJS        = $(SRCS:.c=.o)

MLX_DIR     = minilibx
MLX_LIB     = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "Compilation complete!"

$(MLX_LIB):
	@echo "Building MiniLibX..."
	@make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
