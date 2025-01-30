/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_logic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:22:22 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 15:57:31 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	register_key(int keycode, void *param)
{
	static int	moves;
	t_all		*all;
	t_game		*game;

	all = (t_all *)param;
	game = &all->game;
	if (keycode == 65307)
		close_window(all);
	if (keycode == 119)
		check_and_move_player(all, game->player_x, game->player_y - 1, 0);
	if (keycode == 97)
		check_and_move_player(all, game->player_x - 1, game->player_y, -1);
	if (keycode == 115)
		check_and_move_player(all, game->player_x, game->player_y + 1, 0);
	if (keycode == 100)
		check_and_move_player(all, game->player_x + 1, game->player_y, 1);
	if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100)
	{
		moves++;
		if (moves == game->moves)
			ft_printf("moves: %i\n", game->moves);
		moves = game->moves;
	}
	return (EXIT_SUCCESS);
}

int	check_and_move_player(t_all *all, int new_x, int new_y, int direc)
{
	if (all->maps.map[new_y][new_x] == '1')
		return (EXIT_SUCCESS);
	all->game.moves++;
	mlx_put_image_to_window(all->mini.mlx, all->mini.win,
		all->img.floor_img, all->game.player_x * all->maps.scale_factor * 50,
		all->game.player_y * all->maps.scale_factor * 50);
	if (all->maps.map[new_y][new_x] == 'C')
	{
		all->game.collec_count--;
		all->maps.map[new_y][new_x] = '0';
	}
	if (all->maps.map[new_y][new_x] == 'E')
	{
		if (all->game.collec_count == 0)
		{
			close_window(all);
			return (EXIT_FAILURE);
		}
	}
	all->game.player_x = new_x;
	all->game.player_y = new_y;
	draw_floor_and_player(*all, new_x, new_y, direc);
	if (all->game.collec_count == 0)
		draw_img(*all, all->img.exit_img, 'E');
	return (EXIT_SUCCESS);
}

void	draw_floor_and_player(t_all all, int x, int y, int direc)
{
	static int	last_direction = 1;
	int			position_x;
	int			position_y;

	position_x = x * all.maps.scale_factor * 50;
	position_y = y * all.maps.scale_factor * 50;
	mlx_put_image_to_window(all.mini.mlx, all.mini.win, 
		all.img.floor_img, position_x, position_y);
	if (direc == -1)
		last_direction = -1;
	else if (direc == 1)
		last_direction = 1;
	if (last_direction == -1)
		mlx_put_image_to_window(all.mini.mlx, all.mini.win, 
			all.img.player_l_img, position_x, position_y);
	else
		mlx_put_image_to_window(all.mini.mlx, all.mini.win, 
			all.img.player_img, position_x, position_y);
}
