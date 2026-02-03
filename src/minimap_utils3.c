/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:58:35 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/13 10:46:29 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_smooth_tile(t_data *game, t_point screen_pos, int color)
{
	t_point	offset;

	offset.y = 0;
	while (offset.y < MINIMAP_TILE_SIZE)
	{
		offset.x = 0;
		while (offset.x < MINIMAP_TILE_SIZE)
		{
			draw_tile_pixel(game, screen_pos, offset, color);
			offset.x++;
		}
		offset.y++;
	}
}

void	calculate_map_position(t_data *game, int minimap_x, int minimap_y,
		t_point *map_pos)
{
	double	player_map_x;
	double	player_map_y;
	int		tiles_per_row;
	int		center_tile_x;
	int		center_tile_y;

	player_map_x = game->player.pos[0] / TILESIZE;
	player_map_y = game->player.pos[1] / TILESIZE;
	tiles_per_row = MINIMAP_SIZE / MINIMAP_TILE_SIZE;
	center_tile_x = tiles_per_row / 2;
	center_tile_y = tiles_per_row / 2;
	map_pos->x = (int)player_map_x + (minimap_x - center_tile_x);
	map_pos->y = (int)player_map_y + (minimap_y - center_tile_y);
}

void	draw_minimap_tile(t_data *game, t_point minimap_pos, t_point map_pos)
{
	t_point	screen_pos;
	char	tile;
	int		color;

	screen_pos.x = MINIMAP_MARGIN + minimap_pos.x * MINIMAP_TILE_SIZE;
	screen_pos.y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + minimap_pos.y
		* MINIMAP_TILE_SIZE;
	if (map_pos.y >= 0 && map_pos.y < game->map_height)
	{
		if (map_pos.x >= 0 && map_pos.x < (int)ft_strlen(game->map[map_pos.y]))
		{
			tile = game->map[map_pos.y][map_pos.x];
			color = get_modern_tile_color(tile);
			draw_smooth_tile(game, screen_pos, color);
		}
		else
			draw_smooth_tile(game, screen_pos, COLOR_VOID);
	}
	else
		draw_smooth_tile(game, screen_pos, COLOR_VOID);
}

void	render_precise_tiles(t_data *game)
{
	int		tiles_per_row;
	t_point	minimap_pos;
	t_point	map_pos;

	tiles_per_row = MINIMAP_SIZE / MINIMAP_TILE_SIZE;
	minimap_pos.y = 0;
	while (minimap_pos.y < tiles_per_row)
	{
		minimap_pos.x = 0;
		while (minimap_pos.x < tiles_per_row)
		{
			calculate_map_position(game, minimap_pos.x, minimap_pos.y,
				&map_pos);
			draw_minimap_tile(game, minimap_pos, map_pos);
			minimap_pos.x++;
		}
		minimap_pos.y++;
	}
}

double	calculate_fov_angle(t_data *game, int direction)
{
	double	player_angle;
	double	fov_angle;

	player_angle = atan2(-game->player.dir[0], game->player.dir[1]);
	fov_angle = M_PI / 3.0;
	return (player_angle + (fov_angle / 2.0) * direction);
}
