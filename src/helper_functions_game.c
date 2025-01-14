#include "solong.h"

void	draw_img(t_mini mini, t_maps maps, void *img, char symbol)
{
	int	y;
	int	x;

	y = -1;
	while (++y < maps.rows)
	{
		x = -1;
		while (++x < maps.cols)
		{
			if (symbol == '0' || maps.map[y][x] == symbol)
				mlx_put_image_to_window(mini.mlx, mini.win, img, x * 50, y * 50);
		}
	}
}

int close_window(t_all *all)
{
	if (all->img.wall_img)
		mlx_destroy_image(all->mini.mlx, all->img.wall_img);
	if (all->img.floor_img)
		mlx_destroy_image(all->mini.mlx, all->img.floor_img);
	if (all->img.player_img)
		mlx_destroy_image(all->mini.mlx, all->img.player_img);
	if (all->img.collec_img)
		mlx_destroy_image(all->mini.mlx, all->img.collec_img);
	if (all->img.exit_img)
		mlx_destroy_image(all->mini.mlx, all->img.exit_img);
	all->img.wall_img = NULL;
	all->img.floor_img = NULL;
	all->img.player_img = NULL;
	all->img.collec_img = NULL;
	all->img.exit_img = NULL;
	if (all->mini.win)
	{
		mlx_destroy_window(all->mini.mlx, all->mini.win);
		all->mini.win = NULL;
	}
	exit(0);
	return (0);
}

void error_exit(const char *message)
{
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}
