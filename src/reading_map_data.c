#include "solong.h"

// opens map and allocates first line
int	reading_map_data(const char *filename, t_maps *maps, FILE **file, char **line)
{
	*file = fopen(filename, "r");
	if (!*file)
	{
		perror("Error opening file");
		return (1);
	}
	*line = get_next_line(*file);
	if (!*line)
	{
		fclose(*file);
		return (1);
	}
	if (initialize_map(maps, *line))
	{
		fclose(*file);
		return (1);
	}
	return (0);
}

// first alloc of the map
int	initialize_map(t_maps *maps, char *line)
{
	maps->cols = strlen(line);
	maps->map = malloc(sizeof(char *));
	if (!maps->map)
	{
		free(line);
		perror("Memory allocation failed");
		return (1);
	}
	maps->map[0] = line;
	maps->rows = 1;
	return (0);
}

