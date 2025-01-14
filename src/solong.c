#include "solong.h"

int	main(int argc, char *argv[])
{
	t_all	all;

	all.maps = (t_maps){NULL, 0, 0};
	all.game = (t_game){-1, -1, 0};
	if (handle_map_validation(argc, argv, &all.maps, &all.game))
		return (1);
	if (handle_window(&all) == EXIT_FAILURE)
		return (1);
	free_string(all.maps.map, all.maps.rows);
	return (0);
}


int	handle_map_validation(int argc, char **argv, t_maps *maps, t_game *game)
{
	FILE	*file;
	char	*line;

	if (argc != 2)
	{
		printf("Usage: %s *.ber\n", argv[0]);
		return (1);
	}
	if (check_file_end((char *)argv[1]))
		return (1);
	if (reading_map_data(argv[1], maps, &file, &line))
		return (2);
	if (storing_map_data(maps, file))
	{
		fclose(file);
		return (3);
	}
	fclose(file);
    if (validate_map_symbols(*maps, game))
        return (4);
    if (check_map_reachability(*maps, *game))
        return (5);
	return (0);
}

int	handle_window(t_all *all)
{
	all->mini.mlx = mlx_init();
	if (!all->mini.mlx)
		error_exit("Failed to initialize MLX");
	all->mini.win = mlx_new_window(all->mini.mlx,
			all->maps.cols * 50, all->maps.rows * 50, "So Long");
	if (!all->mini.win)
		error_exit("Failed to create window");
	if (xpm_image(all) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	draw_img(all->mini, all->maps, all->img.floor_img, '0');
	draw_img(all->mini, all->maps, all->img.wall_img, '1');
	draw_img(all->mini, all->maps, all->img.collec_img, 'C');
	draw_img(all->mini, all->maps, all->img.player_img, 'P');
	mlx_key_hook(all->mini.win, (int (*)())register_key, all);
	mlx_hook(all->mini.win, 17, 0, (int (*)())close_window, all);
	mlx_loop(all->mini.mlx);
	return (EXIT_SUCCESS);
}
