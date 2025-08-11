/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:31:05 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/11 12:21:39 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_single_fov_line(t_data *game, t_point center, int direction)
{
	double	angle;
	int		fov_length;
	t_point	end;

	angle = calculate_fov_angle(game, direction);
	fov_length = MINIMAP_TILE_SIZE * 3;
	end.x = center.x + (int)(cos(angle) * fov_length);
	end.y = center.y + (int)(sin(angle) * fov_length);
	draw_line(game, center, end, COLOR_FOV_LINE);
}

static void	draw_fov_lines(t_data *game, int center_x, int center_y)
{
	t_point	center;
	int		i;

	center.x = center_x;
	center.y = center_y;
	i = -1;
	while (i <= 1)
	{
		draw_single_fov_line(game, center, i);
		i += 2;
	}
}

static void	draw_player_direction(t_data *game, int center_x, int center_y)
{
	double	dir_length;
	t_point	center;
	t_point	dir_end;

	dir_length = MINIMAP_PLAYER_SIZE * 1.8;
	center.x = center_x;
	center.y = center_y;
	dir_end.x = center_x + (int)(game->player.dir[0] * dir_length);
	dir_end.y = center_y + (int)(game->player.dir[1] * dir_length);
	draw_line(game, center, dir_end, COLOR_DIRECTION);
	center.x++;
	dir_end.x++;
	draw_line(game, center, dir_end, COLOR_DIRECTION);
	center.x--;
	center.y++;
	dir_end.x--;
	dir_end.y++;
	draw_line(game, center, dir_end, COLOR_DIRECTION);
}

static void	draw_modern_player(t_data *game)
{
	t_point	center;

	center.x = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	center.y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	draw_fov_lines(game, center.x, center.y);
	draw_circle(game, center, MINIMAP_PLAYER_SIZE / 2 + 1, 0x000000);
	draw_circle(game, center, MINIMAP_PLAYER_SIZE / 2, COLOR_PLAYER);
	draw_player_direction(game, center.x, center.y);
}

void	render_minimap(t_data *game)
{
	draw_modern_minimap_background(game);
	render_precise_tiles(game);
	draw_modern_player(game);
}
