#include "solong.h"

int	storing_map_data(t_maps *maps, FILE *file)
{
	char	*line;

	line = get_next_line(file);
	while (line != NULL)
	{
		if (strlen(line) != (size_t)maps->cols)
			return (handle_line_error(maps, line));
		if (realloc_map(maps, line))
			return (1);
		line = get_next_line(file);
	}
	return (0);
}
// part of storing_map_data
int	handle_line_error(t_maps *maps, char *line)
{
	fprintf(stderr, "Error: Map is not a rectangle\n");
	free(line);
	free_string(maps->map, maps->rows);
	return (1);
}

// allocates another line
int	realloc_map(t_maps *maps, char *line)
{
	char	**new_map;

	new_map = realloc(maps->map, (maps->rows + 1) * sizeof(char *));
	if (!new_map)
	{
		free(line);
		free_string(maps->map, maps->rows);
		perror("Memory reallocation failed");
		return (1);
	}
	maps->map = new_map;
	maps->map[maps->rows] = line;
	maps->rows++;
	return (0);
}
