/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:36:48 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/07 11:38:23 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_spaces_to_walls(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == ' ')
				data->map[y][x] = '1';
			x++;
		}
		y++;
	}
}

int	file_exists(char *filename)
{
	int	fd;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	check_files(t_config *config)
{
	if (!file_exists(config->texture_north))
		return (printf("Error: North texture file not found: %s\n",
				config->texture_north), 0);
	if (!file_exists(config->texture_south))
		return (printf("Error: South texture file not found: %s\n",
				config->texture_south), 0);
	if (!file_exists(config->texture_west))
		return (printf("Error: West texture file not found: %s\n",
				config->texture_west), 0);
	if (!file_exists(config->texture_est))
		return (printf("Error: East texture file not found: %s\n",
				config->texture_est), 0);
	return (1);
}

int	check_player_not_trapped(t_data *data)
{
	int	x;
	int	y;
	int	accessible_neighbors;

	x = data->player.pos[0];
	y = data->player.pos[1];
	accessible_neighbors = 0;
	if (x > 0 && data->map[y][x - 1] == '0')
		accessible_neighbors++;
	if (x < (int)ft_str_len(data->map[y]) - 1 && data->map[y][x + 1] == '0')
		accessible_neighbors++;
	if (y > 0 && data->map[y - 1][x] == '0')
		accessible_neighbors++;
	if (y < data->map_height - 1 && data->map[y + 1][x] == '0')
		accessible_neighbors++;
	if (accessible_neighbors == 0)
	{
		printf("Error: no accessible spaces around player position\n");
		return (0);
	}
	return (1);
}

int	check_map(t_data *data)
{
	if (!data->map || data->map_height == 0)
		return (printf("Error: Empty map\n"), 0);
	if (data->config.floor_color == -1)
		return (printf("Error: Missing floor color (F)\n"), 0);
	if (data->config.ceiling_color == -1)
		return (printf("Error: Missing ceiling color (C)\n"), 0);
	if (!data->config.texture_north || !data->config.texture_south
		|| !data->config.texture_west || !data->config.texture_est)
		return (printf("Error: Missing texture(s)\n"), 0);
	if (!check_content(data))
		return (printf("Error: Invalid characters in map\n"), 0);
	if (!find_player(data))
		return (0);
	if (!check_walls(data))
		return (printf("Error: Map is not closed by walls\n"), 0);
	if (!check_spaces(data))
		return (printf("Error: Invalid space configuration\n"), 0);
	convert_spaces_to_walls(data);
	if (!check_player_not_trapped(data))
		return (0);
	if (!check_path(data))
		return (printf("Error: Player area is not properly enclosed\n"), 0);
	if (!check_files(&data->config))
		return (printf("Error: Texture files not found\n"), 0);
	return (1);
}
