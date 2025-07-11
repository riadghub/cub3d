#include "cub3d.h"

void print_map(t_data *data)
{
	int i;

	printf("=== CARTE ===\n");
	printf("Dimensions: %d x %d\n", data->map_width, data->map_height);
	printf("Joueur: (%d, %d) direction '%c'\n",
		data->player.x, data->player.y, data->player.direction);
	
	if (!data->map)
	{
		printf("ERREUR: data->map est NULL!\n");
		return;
	}
	
	i = 0;
	while (i < data->map_height)
	{
		printf("[%d] %s\n", i, data->map[i]);
		i++;
	}
	printf("============\n");
}

void cleanup_map(t_data *data)
{
	int i;

	if (!data->map)
		return;

	i = 0;
	while (i < data->map_height)
	{
		if (data->map[i])
			free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
	data->map_height = 0;
	data->map_width = 0;
}

int find_player(t_data *data)
{
	int y;
	int x;
	int count;

	y = 0;
	count = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S' ||
				data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				count++;
				data->player.x = x;
				data->player.y = y;
				data->player.direction = data->map[y][x];
				data->map[y][x] = '0'; // Remplacer par un espace vide
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0); // Aucun joueur trouvé
}
