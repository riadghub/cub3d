/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:03:25 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/29 11:43:12 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_pixels(t_data *game, int x, void *texture, int draw_start,
		int draw_end)
{
	int	y;
	int	tex_x;
	int	color;

	calculate_texture_x(game, &tex_x, 64);
	y = draw_start;
	while (y < draw_end)
	{
		calculate_texture_y_and_color(game, texture, tex_x, y, &color);
		put_pixel(game, x, y, color);
		y++;
	}
}

void	calculate_draw_bounds(double distance, int *draw_start, int *draw_end)
{
	double	line_height;
	double	exact_start;

	line_height = (double)WINDOW_HEIGHT / distance * TILESIZE;
	exact_start = ((double)WINDOW_HEIGHT - line_height) / 2.0;
	*draw_start = (int)(exact_start);
	*draw_end = (int)(exact_start + line_height + 0.999);
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= WINDOW_HEIGHT)
		*draw_end = WINDOW_HEIGHT;
}

void	draw_wall_column(t_data *game, int x, double distance)
{
	int		draw_start;
	int		draw_end;
	void	*current_texture;

	game->config.distance = distance;
	calculate_draw_bounds(distance, &draw_start, &draw_end);
	select_wall_texture(game, &current_texture);
	draw_line(game, x, 0, x, draw_start, game->config.ceiling_color);
	draw_wall_pixels(game, x, current_texture, draw_start, draw_end);
	draw_line(game, x, draw_end, x, WINDOW_HEIGHT, game->config.floor_color);
}

void	render(t_data *game)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	distance;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		ray_dir_x = game->player.dir[0] + game->player.plane[0] * camera_x;
		ray_dir_y = game->player.dir[1] + game->player.plane[1] * camera_x;
		distance = cast_ray_dda(game, ray_dir_x, ray_dir_y);
		draw_wall_column(game, x, distance);
		x++;
	}
}
