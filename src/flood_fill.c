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

void	flood_fill(char **map, int x, int y, t_data *data, int *valid)
{
	char	current_char;

	if (*valid == 0)
	{
		return ;
	}
	if (y < 0 || y >= data->map_height)
	{
		return ;
	}
	if (x < 0 || x >= (int)ft_str_len(map[y]))
	{
		return ;
	}
	current_char = map[y][x];
	if (current_char == '1' || current_char == 'V')
	{
		return ;
	}
	if (current_char == ' ')
	{
		return ;
	}
	if (is_border(data, x, y))
	{
		*valid = 0;
		return ;
	}
	map[y][x] = 'V';
	flood_fill(map, x - 1, y, data, valid);
	flood_fill(map, x + 1, y, data, valid);
	flood_fill(map, x, y - 1, data, valid);
	flood_fill(map, x, y + 1, data, valid);
}
