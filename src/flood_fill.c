/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:41:51 by lsadi             #+#    #+#             */
/*   Updated: 2025/08/07 11:22:16 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_max_width(t_data *data)
{
	int	max_width;
	int	current_width;
	int	i;

	max_width = 0;
	i = 0;
	while (i < data->map_height)
	{
		current_width = ft_str_len(data->map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int	is_border(t_data *data, int x, int y)
{
	int	max_width;

	max_width = get_max_width(data);
	if (y == 0 || y == data->map_height - 1)
		return (1);
	if (x == 0 || x == max_width - 1)
		return (1);
	return (0);
}

void	flood_fill(char **map, t_point pos, t_data *data, int *valid)
{
	if (*valid == 0)
		return ;
	if (pos.y < 0 || pos.y >= data->map_height)
		return ;
	if (pos.x < 0 || pos.x >= (int)ft_str_len(map[pos.y]))
		return ;
	if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == 'V')
		return ;
	if (map[pos.y][pos.x] == ' ')
		return ;
	if (is_border(data, pos.x, pos.y))
	{
		*valid = 0;
		return ;
	}
	map[pos.y][pos.x] = 'V';
	flood_fill(map, (t_point){pos.x - 1, pos.y}, data, valid);
	flood_fill(map, (t_point){pos.x + 1, pos.y}, data, valid);
	flood_fill(map, (t_point){pos.x, pos.y - 1}, data, valid);
	flood_fill(map, (t_point){pos.x, pos.y + 1}, data, valid);
}
