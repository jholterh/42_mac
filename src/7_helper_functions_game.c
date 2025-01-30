/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_game.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:22:27 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 15:30:03 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	draw_img(t_all all, void *img, char symbol)
{
	int	y;
	int	x;

	y = -1;
	while (++y < all.maps.rows)
	{
		x = -1;
		while (++x < all.maps.cols)
		{
			if (symbol == '0' || all.maps.map[y][x] == symbol)
				mlx_put_image_to_window(all.mini.mlx, all.mini.win, img,
					x * all.maps.scale_factor * 50,
					y * all.maps.scale_factor * 50);
		}
	}
}

void	destroy_images(t_all *all)
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
	if (all->img.player_l_img)
		mlx_destroy_image(all->mini.mlx, all->img.player_l_img);
}

void	reset_image_pointers(t_all *all)
{
	all->img.wall_img = NULL;
	all->img.floor_img = NULL;
	all->img.player_img = NULL;
	all->img.player_l_img = NULL;
	all->img.collec_img = NULL;
	all->img.exit_img = NULL;
}

int	close_window(t_all *all)
{
	ft_printf("moves: %i\n", all->game.moves);
	destroy_images(all);
	reset_image_pointers(all);
	if (all->mini.win)
	{
		mlx_destroy_window(all->mini.mlx, all->mini.win);
		all->mini.win = NULL;
	}
	mlx_destroy_display(all->mini.mlx);
	free(all->mini.mlx);
	free_string(all->maps.map, all->maps.rows);
	exit(0);
	return (0);
}
