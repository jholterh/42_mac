/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_storing_map_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:22:40 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 17:28:44 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	storing_map_data(t_maps *maps, int fd)
{
	char	*line;
	size_t	len;

	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
			len--;
		}
		if (len != (size_t)maps->cols)
		{
			free(line);
			ft_printf("Error: Map is not a rectangle\n");
			return (EXIT_FAILURE);
		}
		if (realloc_map(maps, line))
			return (EXIT_FAILURE);
		line = ft_get_next_line(fd);
	}
	return (EXIT_SUCCESS);
}

int	realloc_map(t_maps *maps, char *line)
{
	char	**new_map;

	new_map = ft_realloc(maps->map, (maps->rows + 1) * sizeof(char *),
			maps->rows * sizeof(char *));
	if (!new_map)
	{
		free(line);
		free_string(maps->map, maps->rows);
		ft_printf("ERROR: Memory reallocation failed\n");
		return (EXIT_FAILURE);
	}
	maps->map = new_map;
	maps->map[maps->rows] = line;
	maps->rows++;
	return (EXIT_SUCCESS);
}
