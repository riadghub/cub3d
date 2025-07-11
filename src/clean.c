#include "cub3d.h"

void cleanup_config(t_config *config)
{
	if (config->texture_north)
	{
		free(config->texture_north);
		config->texture_north = NULL;
	}
	if (config->texture_south)
	{
		free(config->texture_south);
		config->texture_south = NULL;
	}
	if (config->texture_west)
	{
		free(config->texture_west);
		config->texture_west = NULL;
	}
	if (config->texture_est)
	{
		free(config->texture_est);
		config->texture_est = NULL;
	}
}

void cleanup_data(t_data *data)
{
	cleanup_config(&data->config);
	cleanup_map(data);
}