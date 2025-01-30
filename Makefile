# Compiler
CC = cc

# Flags
CFLAGS = -Wall -Werror -Wextra -v

# Directories
MLX_DIR = minilibx-linux
HEADER_DIR = header
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft

# Libraries
LIBS = -L$(MLX_DIR) -lmlx -lGL -lX11 -lXext -lpthread -lm -lz \
       -L$(LIBFT_DIR) -lft

# Source files
SRC = src/1_check_file_end.c \
      src/5_check_map_reachability.c \
      src/8_handle_key_logic.c \
      src/helper_functions_check.c \
      src/7_helper_functions_game.c \
      src/6_load_images.c \
      src/2_reading_map_data.c \
      src/so_long.c \
      src/3_storing_map_data.c \
      src/4_validate_map_symbols.c \
      src/9_resize_image.c

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable name
NAME = solong

# Include directories
INCLUDES = -I$(MLX_DIR) -I$(HEADER_DIR)

# Rules
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
