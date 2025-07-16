/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:25:07 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/16 15:47:48 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	init_ray(t_data *game, double angle)
{
	game->ray->rayAngle = normalize_angle(angle);
}

// void	render(t_ray *ray)
// {
// 	int		i;
// 	double	angle_step;
// 	double	ray_angle;
// 	double	end_x;
// 	double	end_y;

// 	ray->start_angle = ray->game->player.rotationAngle - (FOV / 2);
// 	angle_step = FOV / NUM_RAYS;
// 	i = 0;
// 	while (i < NUM_RAYS)
// 	{
// 		ray_angle = ray->start_angle + i * angle_step;
// 		ray_angle = normalize_angle(ray_angle);
// 		end_x = ray->game->player.x + cos(ray_angle) * 100;
// 		end_y = ray->game->player.y + sin(ray_angle) * 100;
// 		draw_line(ray->game->img, (int)ray->game->player.x,
// 			(int)ray->game->player.y, (int)end_x, (int)end_y, 0xFF0000);
// 		i++;
// 	}
// }

void	render(t_ray *ray)
{
	int		i;
	double	angle_step;
	double	ray_angle;
	double	end_x;
	double	end_y;
	double	step_x;
	double	step_y;
	int		steps;
	int		max_distance;
	int		map_x;
	int		map_y;

	max_distance = 500;
	ray->start_angle = ray->game->player.rotationAngle - (FOV / 2);
	angle_step = FOV / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = ray->start_angle + i * angle_step;
		ray_angle = normalize_angle(ray_angle);
		step_x = cos(ray_angle);
		step_y = sin(ray_angle);
		end_x = ray->game->player.x;
		end_y = ray->game->player.y;
		steps = 0;
		while (steps < max_distance)
		{
			end_x += step_x;
			end_y += step_y;
			map_x = (int)(end_x / TILESIZE);
			map_y = (int)(end_y / TILESIZE);
			if (map_x < 0 || map_x >= WINDOW_WIDTH || map_y < 0
				|| map_y >= WINDOW_HEIGHT
				|| ray->game->map[map_y][map_x] == '1')
			{
				break ;
			}
			steps++;
		}
		draw_line(ray->game->img, (int)ray->game->player.x,
			(int)ray->game->player.y, (int)end_x, (int)end_y, 0xFF0000);
		i++;
	}
}
