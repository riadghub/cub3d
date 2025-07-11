#include "cub3d.h"

static char **allocate_new_map(t_data *data, char *trimmed_line)
{
	char **new_map;
	int i;

	new_map = malloc(sizeof(char *) * (data->map_height + 2));
	if (!new_map)
		return (NULL);

	i = 0;
	while (i < data->map_height)
	{
		new_map[i] = data->map[i];
		i++;
	}
	new_map[data->map_height] = trimmed_line;
	new_map[data->map_height + 1] = NULL;
	
	return (new_map);
}

static void update_map_dimensions(t_data *data, char *trimmed_line)
{
	if ((int)ft_str_len(trimmed_line) > data->map_width)
		data->map_width = ft_str_len(trimmed_line);
	data->map_height++;
}

void add_map_line(t_data *data, char *line)
{
	char **new_map;
	char *trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n");
	if (!trimmed_line)
		return;

	new_map = allocate_new_map(data, trimmed_line);
	if (!new_map)
	{
		free(trimmed_line);
		return;
	}

	if (data->map)
		free(data->map);
	data->map = new_map;
	update_map_dimensions(data, trimmed_line);
}