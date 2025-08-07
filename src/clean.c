/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:45:51 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/07 11:08:59 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_config(t_config *config, t_data *data)
{
	if (config->texture_north)
	{
		mlx_destroy_image(data->mlx, config->texture_north);
		config->texture_north = NULL;
	}
	if (config->texture_south)
	{
		mlx_destroy_image(data->mlx, config->texture_south);
		config->texture_south = NULL;
	}
	if (config->texture_west)
	{
		mlx_destroy_image(data->mlx, config->texture_west);
		config->texture_west = NULL;
	}
	if (config->texture_est)
	{
		mlx_destroy_image(data->mlx, config->texture_est);
		config->texture_est = NULL;
	}
}

void	cleanup_mlx_data(t_data *data)
{
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->img && data->mlx)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	cleanup_data(t_data *data)
{
	free_textures(data);
	free_texture_paths(data);
	cleanup_mlx_data(data);
	cleanup_map(data);
}
