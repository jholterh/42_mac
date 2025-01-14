#include "solong.h"

int	register_key(int keycode, void *param)
{
    static int moves;
	t_all	*all;
	t_game	*game;

	all = (t_all *)param;
	game = &all->game;
	if (keycode == 53)
		close_window(all);
	if (keycode == 13)
		check_and_move_player(all, game->player_x, game->player_y - 1);
	if (keycode == 0)
		check_and_move_player(all, game->player_x - 1, game->player_y);
	if (keycode == 1)
		check_and_move_player(all, game->player_x, game->player_y + 1);
	if (keycode == 2)
		check_and_move_player(all, game->player_x + 1, game->player_y);
    moves++;
    printf("moves: %i\n", moves);
	return (0);
}

int	check_and_move_player(t_all *all, int new_x, int new_y)
{
	if (all->maps.map[new_y][new_x] == '1')
		return (0);
	mlx_put_image_to_window(all->mini.mlx, all->mini.win,
		all->img.floor_img, all->game.player_x * 50,
		all->game.player_y * 50);
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
			return (1);
		}
	}
	all->game.player_x = new_x;
	all->game.player_y = new_y;
	draw_floor_and_player(all->mini, all->img, new_x, new_y);
	if (all->game.collec_count == 0)
		draw_img(all->mini, all->maps, all->img.exit_img, 'E');
	return (1);
}

void draw_floor_and_player(t_mini mini, t_img img, int x, int y)
{
    mlx_put_image_to_window(mini.mlx, mini.win, img.floor_img, x * 50, y * 50);
    mlx_put_image_to_window(mini.mlx, mini.win, img.player_img, x * 50, y * 50);
}
