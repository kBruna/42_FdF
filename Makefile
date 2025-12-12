NAME        = fdf

CFLAGS		= -Wall -Wextra -Werror -g3
CFLAGS     += -Iincludes -Iminilibx -I. -Isrc/Libft/includes

SRCS        = $(shell find src -name "*.c")

OBJS        = $(SRCS:.c=.o)

MLX_DIR     = minilibx
MLX_LIB 	= $(MLX_DIR)/libmlx.a

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
	#MacOs
	CC			= gcc-15
	MLX_FLAGS 	= -Lmlx -lmlx -framework OpenGL -framework AppKit
	CFLAGS 		+= -fsanitize=address,undefined -o0 -DGL_SILENCE_DEPRECATION -Wno-deprecated-declarations 
else
	#Linux
	CC          = cc
	MLX_FLAGS   = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
endif

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
