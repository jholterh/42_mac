/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_resize_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:53:15 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 17:29:30 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	*resize_image(t_all *all, void *old_img)
{
	double	scale_factor;
	int		new_width;
	int		new_height;
	void	*new_img;

	scale_factor = all->maps.scale_factor;
	new_width = (int)(all->mini.img_width * scale_factor);
	new_height = (int)(all->mini.img_height * scale_factor);
	new_img = mlx_new_image(all->mini.mlx, new_width, new_height);
	if (!new_img)
	{
		ft_printf("ERROR: Failed to create new image.\n");
		return (NULL);
	}
	copy_image_data(all, old_img, new_img, scale_factor);
	return (new_img);
}

void	copy_image_data(t_all *all, void *old_img, void *new_img,
double scale_factor)
{
	t_image_data	img_data;

	img_data.new_width = (int)(all->mini.img_width * scale_factor);
	img_data.new_height = (int)(all->mini.img_height * scale_factor);
	img_data.old_img_addr = (int *)mlx_get_data_addr(old_img, &(int){0},
			&(int){0}, &(int){0});
	img_data.new_img_addr = (int *)mlx_get_data_addr(new_img, &(int){0},
			&(int){0}, &(int){0});
	img_data.scale_factor = scale_factor;
	fill_new_image(all, &img_data);
}

void	fill_new_image(t_all *all, t_image_data *img_data)
{
	int	i;
	int	j;
	int	orig_i;
	int	orig_j;

	i = 0;
	while (i < img_data->new_height)
	{
		j = 0;
		while (j < img_data->new_width)
		{
			orig_i = (int)(i / img_data->scale_factor);
			orig_j = (int)(j / img_data->scale_factor);
			img_data->new_img_addr[i * img_data->new_width + j]
				= img_data->old_img_addr[orig_i * all->mini.img_width + orig_j];
			j++;
		}
		i++;
	}
}

void	calc_scalefactor(t_all *all)
{
	int	max_width;
	int	max_height;
	int	rows;
	int	cols;

	max_width = 36;
	max_height = 20;
	rows = all->maps.rows;
	cols = all->maps.cols;
	while (cols > max_width || rows > max_height)
	{
		all->maps.scale_factor /= 2.0;
		cols /= 2;
		rows /= 2;
	}
}
