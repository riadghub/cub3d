/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:21:41 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/07 11:22:59 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_map(t_data *data)
{
	char	**dup_map;
	int		i;

	dup_map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!dup_map)
		return (NULL);
	i = 0;
	while (i < data->map_height)
	{
		dup_map[i] = ft_strdup(data->map[i]);
		if (!dup_map[i])
		{
			while (--i >= 0)
				free(dup_map[i]);
			free(dup_map);
			return (NULL);
		}
		i++;
	}
	dup_map[data->map_height] = NULL;
	return (dup_map);
}

void	free_copy(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	check_path(t_data *data)
{
	char	**map_copy;
	int		valid;
	t_point	player_pos;

	map_copy = copy_map(data);
	if (!map_copy)
		return (0);
	valid = 1;
	player_pos.x = data->player.pos[0];
	player_pos.y = data->player.pos[1];
	flood_fill(map_copy, player_pos, data, &valid);
	free_copy(map_copy, data->map_height);
	return (valid);
}
