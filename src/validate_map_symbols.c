# include "solong.h"

int	validate_map_symbols(t_maps temp, t_game *game)
{
	int		i;
	int		j;
	char	c;
	int		count[] = {0, 0, 0, 0, 0};

	i = -1;
	while (++i < temp.rows)
	{
		j = -1;
		while (++j < temp.cols)
		{
			c = temp.map[i][j];
			if (validate_walls_symbols(temp, c, i, j))
				return (1);
			if (analyze_map_symbols(c, count, game, i, j))
				return (1);
		}
	}
	if (count[3] == 0 || count[2] == 0 || count[4] == 0)
	{
		printf("There is something missing\n");
		return (1);
	}
	game->collec_count = count[2];
	return (0);
}

int	validate_walls_symbols(t_maps temp, char c, int i, int j)
{
	if (i == 0 || i == temp.rows - 1 || j == 0 || j == temp.cols - 1)
	{
		if (c != '1')
		{
			printf("Outside wall not there\n");
			return (1);
		}
	}
	if (!(strchr("01CPE", c)))
	{
		printf("Map has an undefined symbol\n");
		return (1);
	}
	return (0);
}

int	analyze_map_symbols(char c, int *count, t_game *game, int i, int j)
{
	if (c == '1')
		count[1]++;
	else if (c == 'C')
		count[2]++;
	else if (c == 'E')
	{
		count[3]++;
		if (count[3] > 1)
		{
			printf("More than one exit\n");
			return (1);
		}
	}
	else if (c == 'P')
	{
		count[4]++;
		game->player_x = j;
		game->player_y = i;
		if (count[4] > 1)
		{
			printf("Multiplayer is not supported\n");
			return (1);
		}
	}
	return (0);
}

