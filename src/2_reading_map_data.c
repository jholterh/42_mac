/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_reading_map_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:22:34 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/30 17:31:06 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	reading_map_data(const char *filename, t_maps *maps, char **line)
{
	maps->fd = open(filename, O_RDONLY);
	if (maps->fd == -1)
	{
		ft_printf("ERROR: Couldn't open the file\n");
		return (EXIT_FAILURE);
	}
	*line = ft_get_next_line(maps->fd);
	if (!*line)
	{
		close(maps->fd);
		return (1);
	}
	if (initialize_map(maps, *line))
	{
		close(maps->fd);
		return (1);
	}
	return (0);
}

int	initialize_map(t_maps *maps, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
		len--;
	}
	return (setup_map(maps, line, len));
}

int	setup_map(t_maps *maps, char *line, size_t len)
{
	maps->cols = len;
	maps->map = malloc(sizeof(char *));
	if (!maps->map)
	{
		free(line);
		ft_printf("ERROR: Memory allocation failed\n");
		return (EXIT_FAILURE);
	}
	maps->map[0] = line;
	maps->rows = 1;
	return (EXIT_SUCCESS);
}
