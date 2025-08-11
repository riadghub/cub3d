/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:57:08 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/11 11:58:11 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_border(t_data *game, t_point start)
{
	t_point	pos;
	t_point	distance;

	pos.y = start.y - MINIMAP_BORDER_SIZE;
	while (pos.y < start.y + MINIMAP_SIZE + MINIMAP_BORDER_SIZE)
	{
		pos.x = start.x - MINIMAP_BORDER_SIZE;
		while (pos.x < start.x + MINIMAP_SIZE + MINIMAP_BORDER_SIZE)
		{
			if (pos.x >= 0 && pos.x < WINDOW_WIDTH && pos.y >= 0
				&& pos.y < WINDOW_HEIGHT)
			{
				distance = calculate_border_distance(pos, start);
				if (distance.x * distance.x + distance.y
					* distance.y <= MINIMAP_BORDER_SIZE * MINIMAP_BORDER_SIZE)
					put_pixel(game, pos.x, pos.y, COLOR_MINIMAP_BORDER);
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_minimap_background(t_data *game, t_point start)
{
	t_point	pos;

	pos.y = start.y;
	while (pos.y < start.y + MINIMAP_SIZE)
	{
		pos.x = start.x;
		while (pos.x < start.x + MINIMAP_SIZE)
		{
			if (pos.x >= 0 && pos.x < WINDOW_WIDTH && pos.y >= 0
				&& pos.y < WINDOW_HEIGHT)
				put_pixel(game, pos.x, pos.y, COLOR_MINIMAP_BG);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_modern_minimap_background(t_data *game)
{
	t_point	start;

	start.x = MINIMAP_MARGIN;
	start.y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN;
	draw_minimap_border(game, start);
	draw_minimap_background(game, start);
}

int	get_wall_pixel_color(int x, int y, int color)
{
	if (x == 0 || y == 0 || x == MINIMAP_TILE_SIZE - 1 || y == MINIMAP_TILE_SIZE
		- 1)
		return (color - 0x101010);
	else
		return (color);
}

void	draw_tile_pixel(t_data *game, t_point screen_pos, t_point offset,
		int color)
{
	t_point	pixel_pos;
	int		final_color;

	pixel_pos.x = screen_pos.x + offset.x;
	pixel_pos.y = screen_pos.y + offset.y;
	if (is_pixel_in_minimap_bounds(pixel_pos.x, pixel_pos.y))
	{
		if (color == COLOR_WALL)
			final_color = get_wall_pixel_color(offset.x, offset.y, color);
		else
			final_color = color;
		put_pixel(game, pixel_pos.x, pixel_pos.y, final_color);
	}
}
