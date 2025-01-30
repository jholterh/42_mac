/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_check_map_reachability.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:22:16 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 17:31:21 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	check_map_reachability(t_maps maps, t_game game)
{
	char	**temp;

	temp = create_map_copy(maps);
	if (!temp)
		return (EXIT_FAILURE);
	perform_flood_fill(temp, game.player_x, game.player_y);
	if (verify_flood_fill(temp, maps.rows))
	{
		free_string(temp, maps.rows);
		return (EXIT_FAILURE);
	}
	free_string(temp, maps.rows);
	return (EXIT_SUCCESS);
}

char	**create_map_copy(t_maps maps)
{
	char	**temp;
	int		i;

	temp = malloc(maps.rows * sizeof(char *));
	if (!temp)
	{
		ft_printf("ERROR: Failed to allocate memory for temp map\n");
		return (NULL);
	}
	i = -1;
	while (++i < maps.rows)
	{
		temp[i] = ft_strdup(maps.map[i]);
		if (!temp[i])
		{
			ft_printf("ERROR: Failed to duplicate map line\n");
			free_string(temp, i);
			return (NULL);
		}
	}
	return (temp);
}

void	perform_flood_fill(char **temp, int x, int y)
{
	if (temp[y][x] == '1' || temp[y][x] == '2')
		return ;
	temp[y][x] = '2';
	perform_flood_fill(temp, x, y + 1);
	perform_flood_fill(temp, x, y - 1);
	perform_flood_fill(temp, x + 1, y);
	perform_flood_fill(temp, x - 1, y);
}

int	verify_flood_fill(char **temp, int rows)
{
	int	i;
	int	j;

	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (temp[i][++j])
		{
			if (!(ft_strchr("012", temp[i][j])))
			{
				ft_printf("ERROR: Flood has not passed\n");
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}
