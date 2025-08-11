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

void	initialize_ray_data(t_data *game, t_ray_data *ray, int *map_x,
		int *map_y)
{
	*map_x = (int)(game->player.pos[0] / TILESIZE);
	*map_y = (int)(game->player.pos[1] / TILESIZE);
	game->config.current_ray_dir_x = ray->ray_dir_x;
	game->config.current_ray_dir_y = ray->ray_dir_y;
}

void	calculate_delta_distances(t_ray_data *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	calculate_step_and_side_dist_x(t_data *game, t_ray_data *ray)
{
	int	map_x;

	map_x = (int)(game->player.pos[0] / TILESIZE);
	if (ray->ray_dir_x < 0)
	{
		(ray->step_x) = -1;
		(ray->side_dist_x) = (game->player.pos[0] / TILESIZE - map_x)
			* ray->delta_dist_x;
	}
	else
	{
		(ray->step_x) = 1;
		(ray->side_dist_x) = (map_x + 1.0 - game->player.pos[0] / TILESIZE)
			* ray->delta_dist_x;
	}
}

void	calculate_step_and_side_dist_y(t_data *game, t_ray_data *ray)
{
	int	map_y;

	map_y = (int)(game->player.pos[1] / TILESIZE);
	if (ray->ray_dir_y < 0)
	{
		(ray->step_y) = -1;
		(ray->side_dist_y) = (game->player.pos[1] / TILESIZE - map_y)
			* ray->delta_dist_y;
	}
	else
	{
		(ray->step_y) = 1;
		(ray->side_dist_y) = (map_y + 1.0 - game->player.pos[1] / TILESIZE)
			* ray->delta_dist_y;
	}
}
