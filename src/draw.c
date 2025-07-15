/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:37:49 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/15 15:12:01 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SIZE2 100

void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX,
		int endY, int color)
{
	int		pixels;
	double	deltaX;
	double	deltaY;
	double	pixelX;
	double	pixelY;

	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(mlx, win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

double	get_rotation_angleY(t_data *data)
{
	return (sin(data->player.rotationAngle) * SIZE2 + data->player.y);
}

double	get_rotation_angleX(t_data *data)
{
	return (cos(data->player.rotationAngle) * SIZE2 + data->player.x);
}
