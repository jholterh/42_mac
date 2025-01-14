#ifndef SOLONG_H
#define SOLONG_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

// structures
typedef struct s_maps {
    char **map;
    int rows;
    int cols;
} t_maps;

typedef struct s_game {
    int player_x;
    int player_y;
    int collec_count;
} t_game;

typedef struct s_mini {
    void *mlx;
    void *win;
    int img_width;
    int img_height;
} t_mini;

typedef struct s_img {
    void *wall_img;
    void *floor_img;
    void *player_img;
    void *collec_img;
    void *exit_img;
} t_img;

typedef struct s_all {
    t_maps maps;
    t_mini mini;
    t_img img;
    t_game game;
} t_all;

// functions I have to add later
char *get_next_line(FILE *file);
void free_string(char **str, int str_count);

// handle map validation
int	handle_map_validation(int argc, char **argv, t_maps *maps, t_game *game);

// check file end
int	check_file_end(char *str);

// read map data
int	reading_map_data(const char *filename, t_maps *maps, FILE **file, char **line);
int	initialize_map(t_maps *maps, char *line);

// store map data
int	storing_map_data(t_maps *maps, FILE *file);
int	handle_line_error(t_maps *maps, char *line);
int	realloc_map(t_maps *maps, char *line);

// validate map symbols
int	validate_map_symbols(t_maps temp, t_game *game);
int	validate_walls_symbols(t_maps temp, char c, int i, int j);
int	analyze_map_symbols(char c, int *count, t_game *game, int i, int j);

// check map reachability
int check_map_reachability(t_maps maps, t_game game);
char **create_map_copy(t_maps maps);
void perform_flood_fill(char **temp, int x, int y);
int verify_flood_fill(char **temp, int rows);


// handles the window
int	handle_window(t_all *all);

// loads the images
int xpm_image(t_all *all);
int load_images(t_all *all, const char **paths, void ***images, int num_images);

// handles keys and logic
int	register_key(int keycode, void *param);
int	check_and_move_player(t_all *all, int new_x, int new_y);
void draw_floor_and_player(t_mini mini, t_img img, int x, int y);

// additional functions
void	draw_img(t_mini mini, t_maps maps, void *img, char symbol);
int close_window(t_all *all);
void error_exit(const char *message);

#endif 
