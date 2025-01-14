# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

# Directories
MLX_DIR = minilibx
HEADER_DIR = header
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC = src/check_file_end.c \
		src/check_map_reachability.c \
		src/handle_key_logic.c \
		src/helper_functions_check.c \
		src/helper_functions_game.c \
		src/load_images.c \
		src/reading_map_data.c \
		src/solong.c \
		src/storing_map_data.c \
		src/validate_map_symbols.c

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable name
NAME = solong

# Libraries
LIBS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lz

# Include directories
INCLUDES = -I$(MLX_DIR) -I$(HEADER_DIR)

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all
