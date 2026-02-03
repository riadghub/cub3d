/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:54:57 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/11 11:56:37 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_modern_tile_color(char tile)
{
	if (tile == '1')
		return (COLOR_WALL);
	else if (tile == '0')
		return (COLOR_FLOOR);
	else
		return (COLOR_VOID);
}

int	is_pixel_in_minimap_bounds(int pixel_x, int pixel_y)
{
	if (pixel_x >= MINIMAP_MARGIN && pixel_x < MINIMAP_MARGIN + MINIMAP_SIZE
		&& pixel_y >= WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN
		&& pixel_y < WINDOW_HEIGHT - MINIMAP_MARGIN)
		return (1);
	return (0);
}

void	draw_circle_pixel(t_data *game, t_point center, t_point offset,
		int color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = center.x + offset.x;
	pixel_y = center.y + offset.y;
	if (is_pixel_in_minimap_bounds(pixel_x, pixel_y))
		put_pixel(game, pixel_x, pixel_y, color);
}

void	draw_circle(t_data *game, t_point center, int radius, int color)
{
	t_point	offset;

	offset.y = -radius;
	while (offset.y <= radius)
	{
		offset.x = -radius;
		while (offset.x <= radius)
		{
			if (offset.x * offset.x + offset.y * offset.y <= radius * radius)
				draw_circle_pixel(game, center, offset, color);
			offset.x++;
		}
		offset.y++;
	}
}

t_point	calculate_border_distance(t_point pos, t_point start)
{
	t_point	distance;

	distance.x = 0;
	distance.y = 0;
	if (pos.x < start.x)
		distance.x = start.x - pos.x;
	else if (pos.x >= start.x + MINIMAP_SIZE)
		distance.x = pos.x - (start.x + MINIMAP_SIZE - 1);
	if (pos.y < start.y)
		distance.y = start.y - pos.y;
	else if (pos.y >= start.y + MINIMAP_SIZE)
		distance.y = pos.y - (start.y + MINIMAP_SIZE - 1);
	return (distance);
}
