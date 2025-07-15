/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:45:42 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/15 14:10:45 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_data *data)
{
	int	i;

	printf("=== CARTE ===\n");
	printf("Dimensions: %d x %d\n", data->map_width, data->map_height);
	printf("Joueur: (%f, %f) direction '%c'\n", data->player.x, data->player.y,
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

static int	count_players(t_data *data, int *player_x, int *player_y,
		char *player_direction)
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
				count++;
				if (count == 1)
				{
					*player_x = x;
					*player_y = y;
					*player_direction = data->map[y][x];
				}
			}
			x++;
		}
		y++;
	}
	return (count);
}

int	find_player(t_data *data)
{
	int		count;
	int		player_x;
	int		player_y;
	char	player_direction;

	count = count_players(data, &player_x, &player_y, &player_direction);
	if (count == 1)
	{
		data->player.x = player_x;
		data->player.y = player_y;
		data->player.direction = player_direction;
		data->map[player_y][player_x] = '0';
		return (1);
	}
	return (0);
}

// int is_valid_wall(t_data *data)
// {
//     int i;
//     int j;

//     // Vérifier première et dernière ligne
//     i = 0;
//     while (data->map[0][i])
//     {
//         if (data->map[0][i] != '1' && data->map[0][i] != ' ')
//             return (0);
//         i++;
//     }

//     i = data->map_height - 1;
//     j = 0;
//     while (data->map[i][j])
//     {
//         if (data->map[i][j] != '1' && data->map[i][j] != ' ')
//             return (0);
//         j++;
//     }

//     // Vérifier première et dernière colonne de chaque ligne
//     i = 1;
//     while (i < data->map_height - 1)
//     {
//         if (data->map[i][0] != '1' && data->map[i][0] != ' ')
//             return (0);
//         j = ft_strlen(data->map[i]) - 1;
//         if (data->map[i][j] != '1' && data->map[i][j] != ' ')
//             return (0);
//         i++;
//     }
//     return (1);
// }

int	check_content(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '1' && data->map[i][j] != '0'
				&& data->map[i][j] != 'N' && data->map[i][j] != 'S'
				&& data->map[i][j] != 'E' && data->map[i][j] != 'W'
				&& data->map[i][j] != ' ')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

// int	is_valid_map(t_data *data)
// {
// 	if (find_player(data) && is_valid_wall(data) && is_valid_content(data))
// 		return (1);
// 	return (0);
// }
