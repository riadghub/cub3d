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

void	draw_line(t_data *game, t_point begin, t_point end, int color)
{
	int		pixels;
	double	delta_x;
	double	delta_y;
	t_point	current;

	delta_x = end.x - begin.x;
	delta_y = end.y - begin.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	if (pixels == 0)
		return ;
	delta_x /= pixels;
	delta_y /= pixels;
	current.x = begin.x;
	current.y = begin.y;
	while (pixels > 0)
	{
		put_pixel(game, (int)current.x, (int)current.y, color);
		current.x += delta_x;
		current.y += delta_y;
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
