/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:42:11 by lsadi             #+#    #+#             */
/*   Updated: 2025/08/07 11:41:38 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_sides(t_data *data, int i)
{
	int	j;
	int	len;

	j = 0;
	while (data->map[i][j] == ' ')
		j++;
	if (data->map[i][j] && data->map[i][j] != '1')
		return (0);
	len = ft_str_len(data->map[i]);
	j = len - 1;
	while (j >= 0 && data->map[i][j] == ' ')
		j--;
	if (j >= 0 && data->map[i][j] != '1')
		return (0);
	return (1);
}

int	check_walls(t_data *data)
{
	int	i;

	if (!check_line(data, 0))
	{
		printf("Error: 1st line of map must contain only walls and spaces\n");
		return (0);
	}
	if (!check_line(data, data->map_height - 1))
		return (0);
	i = 1;
	while (i < data->map_height - 1)
	{
		if (!check_sides(data, i))
			return (printf("Error: line %d borders must be walls\n", i + 1), 0);
		i++;
	}
	return (1);
}

int	check_pos(t_data *data, int x, int y)
{
	if (y < 0 || y >= data->map_height)
		return (1);
	if (x < 0 || x >= (int)ft_str_len(data->map[y]))
		return (1);
	if (data->map[y][x] != '1' && data->map[y][x] != ' ')
		return (0);
	return (1);
}

int	check_around(t_data *data, int x, int y)
{
	if (!check_pos(data, x - 1, y))
		return (0);
	if (!check_pos(data, x + 1, y))
		return (0);
	if (!check_pos(data, x, y - 1))
		return (0);
	if (!check_pos(data, x, y + 1))
		return (0);
	return (1);
}

int	check_spaces(t_data *data)
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
			{
				if (!check_around(data, x, y))
				{
					printf("Error: Invalid space at line %d, column %d\n",
						y + 1, x + 1);
					printf(": spaces must be surrounded by walls or spaces");
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}
