/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:02:54 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/29 11:43:15 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_wall_texture(t_data *game, void **current_texture)
{
	if (game->config.last_wall_hit == 0)
		*current_texture = game->config.texture_north_img;
	else if (game->config.last_wall_hit == 1)
		*current_texture = game->config.texture_south_img;
	else if (game->config.last_wall_hit == 2)
		*current_texture = game->config.texture_west_img;
	else if (game->config.last_wall_hit == 3)
		*current_texture = game->config.texture_est_img;
	else
		*current_texture = game->config.wall;
}

void	calculate_texture_x(t_data *game, int *tex_x, int tex_width)
{
	double	wall_x;

	if (game->config.current_side == 0)
		wall_x = game->config.wall_hit_y;
	else
		wall_x = game->config.wall_hit_x;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * (double)tex_width);
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_x >= tex_width)
		*tex_x = tex_width - 1;
}

void	calculate_texture_y_and_color(t_data *game, void *texture, int tex_x,
		int y, int *color)
{
	int		tex_y;
	double	line_height;
	double	exact_start;
	double	wall_ratio;

	line_height = (double)WINDOW_HEIGHT / game->config.distance * TILESIZE;
	exact_start = ((double)WINDOW_HEIGHT - line_height) / 2.0;
	tex_y = (int)(((double)(y - exact_start) / line_height) * 64);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= 64)
		tex_y = 63;
	*color = get_texture_pixel(texture, tex_x, tex_y, 64, 64);
	wall_ratio = 1.0 - (game->config.distance / (TILESIZE * 20));
	if (wall_ratio < 0.3)
		wall_ratio = 0.3;
	*color = darken_color(*color, wall_ratio);
}
