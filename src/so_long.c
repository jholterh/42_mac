/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_solong.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:22:37 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 17:28:30 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int argc, char *argv[])
{
	t_all	all;

	all.maps = (t_maps){NULL, 0, 0, 0, 1.0};
	all.game = (t_game){-1, -1, 0, 0};
	if (handle_map_validation(argc, argv, &all.maps, &all.game))
	{
		free_string(all.maps.map, all.maps.rows);
		return (EXIT_FAILURE);
	}
	if (handle_window(&all) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free_string(all.maps.map, all.maps.rows);
	return (EXIT_SUCCESS);
}

int	handle_map_validation(int argc, char **argv, t_maps *maps, t_game *game)
{
	char	*line;

	if (argc != 2)
	{
		ft_printf("ERROR: Usage: %s *.ber\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (check_file_end((char *)argv[1]))
		return (EXIT_FAILURE);
	if (reading_map_data(argv[1], maps, &line))
		return (EXIT_FAILURE);
	if (storing_map_data(maps, maps->fd))
	{
		close(maps->fd);
		return (EXIT_FAILURE);
	}
	close(maps->fd);
	if (validate_map_symbols(*maps, game))
		return (EXIT_FAILURE);
	if (check_map_reachability(*maps, *game))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_window(t_all *all)
{
	all->mini.mlx = mlx_init();
	if (!all->mini.mlx)
	{
		ft_printf("ERROR: Failed to initialize MLX\n");
		return (EXIT_FAILURE);
	}
	calc_scalefactor(all);
	all->mini.win = mlx_new_window(all->mini.mlx,
			all->maps.cols * all->maps.scale_factor * 50,
			all->maps.rows * all->maps.scale_factor * 50, "So Long");
	if (!all->mini.win)
	{
		ft_printf("ERROR: Failed to create window\n");
		return (EXIT_FAILURE);
	}
	if (xpm_image(all) != 0)
		return (EXIT_FAILURE);
	draw_img(*all, all->img.floor_img, '0');
	draw_img(*all, all->img.wall_img, '1');
	draw_img(*all, all->img.collec_img, 'C');
	draw_img(*all, all->img.player_img, 'P');
	mlx_key_hook(all->mini.win, (int (*)())register_key, all);
	mlx_hook(all->mini.win, 17, 0, (int (*)())close_window, all);
	mlx_loop(all->mini.mlx);
	return (EXIT_SUCCESS);
}
