/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:25:07 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/25 14:03:45 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_ray_data(t_data *game, double ray_dir_x, double ray_dir_y,
		int *map_x, int *map_y)
{
	*map_x = (int)(game->player.pos[0] / TILESIZE);
	*map_y = (int)(game->player.pos[1] / TILESIZE);
	game->config.current_ray_dir_x = ray_dir_x;
	game->config.current_ray_dir_y = ray_dir_y;
}

void	calculate_delta_distances(double ray_dir_x, double ray_dir_y,
		double *delta_dist_x, double *delta_dist_y)
{
	if (ray_dir_x == 0)
		*delta_dist_x = 1e30;
	else
		*delta_dist_x = fabs(1 / ray_dir_x);
	if (ray_dir_y == 0)
		*delta_dist_y = 1e30;
	else
		*delta_dist_y = fabs(1 / ray_dir_y);
}

void	calculate_step_and_side_dist_x(t_data *game, double ray_dir_x,
		double delta_dist_x, int *step_x, double *side_dist_x)
{
	int	map_x;

	map_x = (int)(game->player.pos[0] / TILESIZE);
	if (ray_dir_x < 0)
	{
		*step_x = -1;
		*side_dist_x = (game->player.pos[0] / TILESIZE - map_x) * delta_dist_x;
	}
	else
	{
		*step_x = 1;
		*side_dist_x = (map_x + 1.0 - game->player.pos[0] / TILESIZE)
			* delta_dist_x;
	}
}

void	calculate_step_and_side_dist_y(t_data *game, double ray_dir_y,
		double delta_dist_y, int *step_y, double *side_dist_y)
{
	int	map_y;

	map_y = (int)(game->player.pos[1] / TILESIZE);
	if (ray_dir_y < 0)
	{
		*step_y = -1;
		*side_dist_y = (game->player.pos[1] / TILESIZE - map_y) * delta_dist_y;
	}
	else
	{
		*step_y = 1;
		*side_dist_y = (map_y + 1.0 - game->player.pos[1] / TILESIZE)
			* delta_dist_y;
	}
}
