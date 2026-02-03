/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 05:19:39 by lsadi             #+#    #+#             */
/*   Updated: 2025/08/07 10:56:13 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*load_texture(void *mlx, char *path)
{
	void	*texture;
	int		width;
	int		height;

	if (!path)
	{
		printf("Error: Texture path is NULL\n");
		exit(1);
	}
	texture = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!texture)
	{
		printf("Error: Failed to load texture: %s\n", path);
		printf("Make sure the file exists and is a valid XMP file\n");
		exit(1);
	}
	return (texture);
}

int	load_all_textures(t_data *game)
{
	if (game->config.texture_north)
		game->config.texture_north_img = load_texture(game->mlx,
				game->config.texture_north);
	if (game->config.texture_south)
		game->config.texture_south_img = load_texture(game->mlx,
				game->config.texture_south);
	if (game->config.texture_west)
		game->config.texture_west_img = load_texture(game->mlx,
				game->config.texture_west);
	if (game->config.texture_est)
		game->config.texture_est_img = load_texture(game->mlx,
				game->config.texture_est);
	return (1);
}

void	free_texture_paths(t_data *data)
{
	if (data->config.texture_north)
	{
		free(data->config.texture_north);
		data->config.texture_north = NULL;
	}
	if (data->config.texture_south)
	{
		free(data->config.texture_south);
		data->config.texture_south = NULL;
	}
	if (data->config.texture_west)
	{
		free(data->config.texture_west);
		data->config.texture_west = NULL;
	}
	if (data->config.texture_est)
	{
		free(data->config.texture_est);
		data->config.texture_est = NULL;
	}
}

void	free_textures(t_data *game)
{
	if (game->config.texture_north_img)
		mlx_destroy_image(game->mlx, game->config.texture_north_img);
	if (game->config.texture_south_img)
		mlx_destroy_image(game->mlx, game->config.texture_south_img);
	if (game->config.texture_west_img)
		mlx_destroy_image(game->mlx, game->config.texture_west_img);
	if (game->config.texture_est_img)
		mlx_destroy_image(game->mlx, game->config.texture_est_img);
}
