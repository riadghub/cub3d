/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:25:07 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/16 12:10:42 by reeer-aa         ###   ########.fr       */
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

void	render(t_ray *ray)
{
	int		i;
	double	start_angle;
	double	angle_step;
	double	ray_angle;
	double	end_x;
	double	end_y;

	start_angle = ray->game->player.rotationAngle - (FOV / 2);
	angle_step = FOV / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = start_angle + i * angle_step;
		ray_angle = normalize_angle(ray_angle);
		end_x = ray->game->player.x + cos(ray_angle) * 100;
		end_y = ray->game->player.y + sin(ray_angle) * 100;
		draw_line(ray->game->mlx, ray->game->win, ray->game->player.x,
			ray->game->player.y, end_x, end_y, 0xFF0000);
		i++;
	}
}
