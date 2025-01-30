/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_load_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:22:31 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 17:30:01 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	xpm_image(t_all *all)
{
	const char	*paths[] = {
		"./resources/wall.xpm",
		"./resources/floor.xpm",
		"./resources/player.xpm",
		"./resources/collec.xpm",
		"./resources/exit.xpm",
		"./resources/player_l.xpm"
	};
	void		**images[6];
	int			num_images;

	images[0] = &all->img.wall_img;
	images[1] = &all->img.floor_img;
	images[2] = &all->img.player_img;
	images[3] = &all->img.collec_img;
	images[4] = &all->img.exit_img;
	images[5] = &all->img.player_l_img;
	num_images = sizeof(paths) / sizeof(paths[0]);
	return (load_images(all, paths, images, num_images));
}

int	load_images(t_all *all, const char **paths, void ***images, int num_images)
{
	int	i;
	int	result;

	i = 0;
	while (i < num_images)
	{
		result = load_and_resize_image(all, paths[i], images[i]);
		if (result == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	load_and_resize_image(t_all *all, const char *path, void **image)
{
	void	*original_img;
	void	*resized_img;

	original_img = mlx_xpm_file_to_image(all->mini.mlx, (char *)path,
			&all->mini.img_width, &all->mini.img_height);
	if (!original_img)
	{
		ft_printf("ERROR: Failed to load image: %s\n", path);
		close_window(all);
		return (EXIT_FAILURE);
	}
	resized_img = resize_image(all, original_img);
	if (!resized_img)
	{
		ft_printf("ERROR: Failed to resize image: %s\n", path);
		mlx_destroy_image(all->mini.mlx, original_img);
		close_window(all);
		return (EXIT_FAILURE);
	}
	mlx_destroy_image(all->mini.mlx, original_img);
	*image = resized_img;
	return (EXIT_SUCCESS);
}
