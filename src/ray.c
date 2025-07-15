/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:46:32 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/15 15:29:47 by reeer-aa         ###   ########.fr       */
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

void	init_ray(t_ray *ray, double angle)
{
	ray->rayAngle = normalize_angle(angle);
}

// void	render(t_ray *ray)
// {
// 	while (ray->rayAngle < FOV)
// 	{
// 		draw_line(ray->game->mlx, ray->game->win, ray->game->player.x,
// 			ray->game->player.y, get_rotation_angleX(ray->game),
// 			get_rotation_angleY(ray->game), 0xFF0000);
// 	}
// }
