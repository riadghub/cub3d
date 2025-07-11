/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:45:42 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/11 16:12:53 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_data *data)
{
	int	i;

	printf("=== CARTE ===\n");
	printf("Dimensions: %d x %d\n", data->map_width, data->map_height);
	printf("Joueur: (%d, %d) direction '%c'\n", data->player.x, data->player.y,
		data->player.direction);
	if (!data->map)
	{
		printf("ERREUR: data->map est NULL!\n");
		return ;
	}
	i = 0;
	while (i < data->map_height)
	{
		printf("[%d] %s\n", i, data->map[i]);
		i++;
	}
	printf("============\n");
}

void	cleanup_map(t_data *data)
{
	int	i;

	if (!data->map)
		return ;
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

int	find_player(t_data *data)
{
	int	count;
	int	x;
	int	y;

	y = 0;
	count = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				count += 1;
				data->player.x = x;
				data->player.y = y;
				data->player.direction = data->map[y][x];
				data->map[y][x] = '0'; // Remplacer par un espace vide
			}
			x++;
		}
		y++;
	}
	if (count == 1)
		return (1);
	return (0);
	// Aucun joueur trouvé
}

int	is_valid_wall(t_data *data)
{
	int	i;
	int	j;
	int	clen;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		clen = ft_strlen(data->map[i]);
		while (data->map[i][j])
		{
			if ((data->map[0][j] && data->map[0][j] != '1') || (data->map[i][0]
					&& data->map[i][0] != '1') || data->map[i][clen - 1] != '1')
			{
				printf("Clen = %d\n", clen);
				printf("Pos de la 1ere cond : 0 %d\nCase : %c\n", j,
					data->map[0][j]);
				printf("Pos de la 2eme cond : %d 0\nCase : %c\n", i,
					data->map[i][0]);
				printf("Pos de la 3eme cond : %d %d\nCase : %c\n", i, clen - 1,
					data->map[i][clen - 1]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	is_valid_content(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ' || data->map[i][j] == '\t')
			{
				data->map[i][j] = '1';
				j++;
			}
			if (data->map[i][j] != '1' && data->map[i][j] != '0'
				&& data->map[i][j] != 'N' && data->map[i][j] != 'S'
				&& data->map[i][j] != 'E' && data->map[i][j] != 'W')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_valid_map(t_data *data)
{
	if (find_player(data) && is_valid_wall(data) && is_valid_content(data))
		return (1);
	return (0);
}
