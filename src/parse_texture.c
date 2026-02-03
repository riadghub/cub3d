/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 05:19:58 by lsadi             #+#    #+#             */
/*   Updated: 2025/08/07 11:52:32 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	assign_north_south_texture(t_config *config, char *path,
		char *direction)
{
	if (ft_strncmp(direction, "NO", 2) == 0)
	{
		if (config->texture_north)
			return (printf("Error: Duplicate North texture\n"), 0);
		config->texture_north = path;
		return (1);
	}
	else if (ft_strncmp(direction, "SO", 2) == 0)
	{
		if (config->texture_south)
			return (printf("Error: Duplicate South texture\n"), 0);
		config->texture_south = path;
		return (1);
	}
	return (-1);
}

static int	assign_west_east_texture(t_config *config, char *path,
		char *direction)
{
	if (ft_strncmp(direction, "WE", 2) == 0)
	{
		if (config->texture_west)
			return (printf("Error: Duplicate West texture\n"), 0);
		config->texture_west = path;
		return (1);
	}
	else if (ft_strncmp(direction, "EA", 2) == 0)
	{
		if (config->texture_est)
			return (printf("Error: Duplicate East texture\n"), 0);
		config->texture_est = path;
		return (1);
	}
	return (-1);
}

int	assign_texture_by_direction(t_config *config, char *path, char *direction)
{
	int	result;

	result = assign_north_south_texture(config, path, direction);
	if (result != -1)
		return (result);
	result = assign_west_east_texture(config, path, direction);
	if (result != -1)
		return (result);
	return (0);
}
