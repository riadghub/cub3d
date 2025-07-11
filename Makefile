NAME = cub3D
MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I get_next_line -I $(MLX_DIR) -I$(LIBFT_DIR) -I /usr/include/X11 -I includes

SRCS = src/main.c \
	src/parse_file.c \
	src/clean.c \
	src/map.c \
	src/parse_map.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a
OBJS = $(SRCS:.c=.o)

get_next_line/%.o: get_next_line/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "cub3D compilé avec succès!"

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "Libft compilée."

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
	@echo "MiniLibX compilée."

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1
	@rm -f $(OBJS)
	@echo "Fichiers objets supprimés."

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@rm -f $(NAME)
	@echo "Nettoyage complet effectué."

re: fclean all

.PHONY: all clean fclean re