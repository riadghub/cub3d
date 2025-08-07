/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:53:32 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/07 11:17:00 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_data *game, int beginX, int beginY, int endX, int endY,
		int color)
{
	int		pixels;
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;

	delta_x = endX - beginX;
	delta_y = endY - beginY;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	if (pixels == 0)
		return ;
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = beginX;
	pixel_y = beginY;
	while (pixels > 0)
	{
		put_pixel(game, (int)pixel_x, (int)pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels--;
	}
}

double	get_rotation_angle_y(t_data *data)
{
	return (data->player.dir[1] * SIZE2 + data->player.pos[1]);
}

double	get_rotation_angle_x(t_data *data)
{
	return (data->player.dir[0] * SIZE2 + data->player.pos[0]);
}
