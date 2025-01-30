/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_validate_map_symbols.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:22:43 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 17:44:25 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	process_map_symbols(t_maps temp, t_analysis_data *data, t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (++i < temp.rows)
	{
		j = -1;
		while (++j < temp.cols)
		{
			c = temp.map[i][j];
			if (validate_walls_symbols(temp, c, i, j))
				return (EXIT_FAILURE);
			data->i = i;
			data->j = j;
			if (analyze_map_symbols(c, data, game))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	validate_map_symbols(t_maps temp, t_game *game)
{
	int				count[5];
	t_analysis_data	data;

	data.count = count;
	data.i = 0;
	data.j = 0;
	ft_bzero(count, sizeof(count));
	if (process_map_symbols(temp, &data, game))
		return (EXIT_FAILURE);
	if (check_missing_elements(count))
		return (EXIT_FAILURE);
	game->collec_count = count[2];
	return (EXIT_SUCCESS);
}

int	check_missing_elements(int *count)
{
	if (count[3] == 0 || count[2] == 0 || count[4] == 0)
	{
		ft_printf("ERROR: There is something missing\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validate_walls_symbols(t_maps temp, char c, int i, int j)
{
	if (i == 0 || i == temp.rows - 1 || j == 0 || j == temp.cols - 1)
	{
		if (c != '1')
		{
			ft_printf("Error: Outside wall not there at position (%d, %d)\n",
				i, j);
			return (EXIT_FAILURE);
		}
	}
	if (!(ft_strchr("01CPE", c)))
	{
		ft_printf("ERROR: Map has an undefined symbol\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	analyze_map_symbols(char c, t_analysis_data *data, t_game *game)
{
	if (c == '1')
		data->count[1]++;
	else if (c == 'C')
		data->count[2]++;
	else if (c == 'E')
	{
		data->count[3]++;
		if (data->count[3] > 1)
		{
			ft_printf("ERROR: More than one exit\n");
			return (EXIT_FAILURE);
		}
	}
	else if (c == 'P')
	{
		data->count[4]++;
		game->player_x = data->j;
		game->player_y = data->i;
		if (data->count[4] > 1)
		{
			ft_printf("ERROR: Multiplayer is not supported\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
