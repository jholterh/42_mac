/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:02:52 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 16:20:25 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include <fcntl.h>    // For open
# include <unistd.h>   // For close
# include <stdlib.h>
# include <mlx.h>
# include "libft.h"

// structures
typedef struct s_maps {
	char	**map;
	int		fd;
	int		rows;
	int		cols;
	double	scale_factor;
}	t_maps;

typedef struct s_game {
	int	player_x;
	int	player_y;
	int	collec_count;
	int	moves;
}	t_game;

typedef struct s_mini {
	void	*mlx;
	void	*win;
	int		img_width;
	int		img_height;
}	t_mini;

typedef struct s_img {
	void	*wall_img;
	void	*floor_img;
	void	*player_img;
	void	*player_l_img;
	void	*collec_img;
	void	*exit_img;
}	t_img;

typedef struct s_all {
	t_maps	maps;
	t_mini	mini;
	t_img	img;
	t_game	game;
}	t_all;

typedef struct s_image_data {
	int		*old_img_addr;
	int		*new_img_addr;
	int		new_width;
	int		new_height;
	double	scale_factor;
}	t_image_data;

typedef struct s_analysis_data {
	int		*count;
	int		i;
	int		j;
}	t_analysis_data;

// functions I have to add later
void	free_string(char **str, int str_count);

// handle map validation
int		handle_map_validation(int argc, char **argv,
			t_maps *maps, t_game *game);

// check file end
int		check_file_end(char *str);

// read map data
int		reading_map_data(const char *filename, t_maps *maps, char **line);
int		initialize_map(t_maps *maps, char *line);
int		setup_map(t_maps *maps, char *line, size_t len);

// store map data
int		storing_map_data(t_maps *maps, int fd);
int		realloc_map(t_maps *maps, char *line);

// validate map symbols
int		process_map_symbols(t_maps temp, t_analysis_data *data, t_game *game);
int		validate_map_symbols(t_maps temp, t_game *game);
int		check_missing_elements(int *count);
int		validate_walls_symbols(t_maps temp, char c, int i, int j);
int		analyze_map_symbols(char c, t_analysis_data *data, t_game *game);

// check map reachability
int		check_map_reachability(t_maps maps, t_game game);
char	**create_map_copy(t_maps maps);
void	perform_flood_fill(char **temp, int x, int y);
int		verify_flood_fill(char **temp, int rows);

// handles the window
int		handle_window(t_all *all);

// loads the images
int		xpm_image(t_all *all);
int		load_images(t_all *all, const char **paths,
			void ***images, int num_images);
int		load_and_resize_image(t_all *all, const char *path, void **image);

// resize the images
void	*resize_image(t_all *all, void *old_img);
void	copy_image_data(t_all *all, void *old_img,
			void *new_img, double scale_factor);
void	fill_new_image(t_all *all, t_image_data *img_data);
void	calc_scalefactor(t_all *all);

// handles keys and logic
int		register_key(int keycode, void *param);
int		check_and_move_player(t_all *all, int new_x, int new_y, int direc);
void	draw_floor_and_player(t_all all, int x, int y, int direc);

// additional functions
void	draw_img(t_all all, void *img, char symbol);
void	destroy_images(t_all *all);
void	reset_image_pointers(t_all *all);
int		close_window(t_all *all);
//void	error_exit(const char *message);

#endif
