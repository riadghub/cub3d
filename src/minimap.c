/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:31:05 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/25 13:47:59 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_inner_background(t_data *game, int start_x,
		int start_y)
{
	int x, y;
	y = start_y;
	while (y < start_y + MINIMAP_SIZE)
	{
		x = start_x;
		while (x < start_x + MINIMAP_SIZE)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				put_pixel(game, x, y, 0x404040);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_background(t_data *game)
{
	int	start_x;
	int	start_y;

	int x, y;
	start_x = MINIMAP_MARGIN;
	start_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN;
	y = start_y - 2;
	while (y < start_y + MINIMAP_SIZE + 2)
	{
		x = start_x - 2;
		while (x < start_x + MINIMAP_SIZE + 2)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				put_pixel(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
	draw_minimap_inner_background(game, start_x, start_y);
}

static void	draw_minimap_tile(t_data *game, int screen_x, int screen_y,
		int color)
{
	int	pixel_x;
	int	pixel_y;

	int x, y;
	y = 0;
	while (y < MINIMAP_TILE_SIZE)
	{
		x = 0;
		while (x < MINIMAP_TILE_SIZE)
		{
			pixel_x = screen_x + x;
			pixel_y = screen_y + y;
			if (pixel_x >= MINIMAP_MARGIN && pixel_x < MINIMAP_MARGIN
				+ MINIMAP_SIZE && pixel_y >= WINDOW_HEIGHT - MINIMAP_SIZE
				- MINIMAP_MARGIN && pixel_y < WINDOW_HEIGHT - MINIMAP_MARGIN)
			{
				put_pixel(game, pixel_x, pixel_y, color);
			}
			x++;
		}
		y++;
	}
}

static void	draw_player_square(t_data *game, int center_x, int center_y)
{
	int	pixel_x;
	int	pixel_y;

	int x, y;
	y = -MINIMAP_PLAYER_SIZE / 2;
	while (y <= MINIMAP_PLAYER_SIZE / 2)
	{
		x = -MINIMAP_PLAYER_SIZE / 2;
		while (x <= MINIMAP_PLAYER_SIZE / 2)
		{
			pixel_x = center_x + x;
			pixel_y = center_y + y;
			if (pixel_x >= MINIMAP_MARGIN && pixel_x < MINIMAP_MARGIN
				+ MINIMAP_SIZE && pixel_y >= WINDOW_HEIGHT - MINIMAP_SIZE
				- MINIMAP_MARGIN && pixel_y < WINDOW_HEIGHT - MINIMAP_MARGIN)
			{
				put_pixel(game, pixel_x, pixel_y, 0xFF0000);
			}
			x++;
		}
		y++;
	}
}

static void	draw_minimap_player(t_data *game)
{
	int		center_x;
	int		center_y;
	double	dir_length;
	int		end_x;
	int		end_y;

	center_x = MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	center_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + MINIMAP_SIZE / 2;
	draw_player_square(game, center_x, center_y);
	dir_length = MINIMAP_TILE_SIZE * 1.5;
	end_x = center_x + (int)(game->player.dir[0] * dir_length);
	end_y = center_y + (int)(game->player.dir[1] * dir_length);
	draw_line(game, center_x, center_y, end_x, end_y, 0xFF4444);
}

static int	get_tile_color(char tile)
{
	int	color;

	if (tile == '1')
		color = 0x808080;
	else if (tile == '0')
		color = 0xE0E0E0;
	else if (tile == ' ')
		color = 0x404040;
	else
		color = 0x604040;
	return (color);
}

static void	process_minimap_tile(t_data *game, double player_map_y,
		int minimap_center_y, int minimap_x, int minimap_y, int map_x)
{
	int		map_y;
	int		screen_x;
	int		screen_y;
	char	tile;
	int		color;

	map_y = (int)player_map_y + (minimap_y - minimap_center_y);
	screen_x = MINIMAP_MARGIN + minimap_x * MINIMAP_TILE_SIZE;
	screen_y = WINDOW_HEIGHT - MINIMAP_SIZE - MINIMAP_MARGIN + minimap_y
		* MINIMAP_TILE_SIZE;
	if (map_x >= 0 && map_x < game->map_width && map_y >= 0
		&& map_y < game->map_height)
	{
		if (map_x < (int)ft_strlen(game->map[map_y]))
		{
			tile = game->map[map_y][map_x];
			color = get_tile_color(tile);
			draw_minimap_tile(game, screen_x, screen_y, color);
		}
	}
}

static void	render_minimap_tiles(t_data *game, double player_map_x,
		double player_map_y)
{
	int	minimap_center_x;
	int	minimap_center_y;
	int	minimap_x;
	int	minimap_y;
	int	map_x;

	minimap_center_x = MINIMAP_SIZE / 2 / MINIMAP_TILE_SIZE;
	minimap_center_y = MINIMAP_SIZE / 2 / MINIMAP_TILE_SIZE;
	minimap_y = 0;
	while (minimap_y < MINIMAP_SIZE / MINIMAP_TILE_SIZE)
	{
		minimap_x = 0;
		while (minimap_x < MINIMAP_SIZE / MINIMAP_TILE_SIZE)
		{
			map_x = (int)player_map_x + (minimap_x - minimap_center_x);
			process_minimap_tile(game, player_map_y, minimap_center_y,
				minimap_x, minimap_y, map_x);
			minimap_x++;
		}
		minimap_y++;
	}
}

void	render_minimap(t_data *game)
{
	double player_map_x;
	double player_map_y;

	player_map_x = game->player.pos[0] / TILESIZE;
	player_map_y = game->player.pos[1] / TILESIZE;
	draw_minimap_background(game);
	render_minimap_tiles(game, player_map_x, player_map_y);
	draw_minimap_player(game);
}
