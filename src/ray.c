/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:25:07 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/25 12:18:28 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_column(t_data *game, int x, double distance)
{
	int		y;
	double	line_height;
	double	exact_start;
	double	exact_end;
	int		draw_start;
	int		draw_end;
	void	*current_texture;
	int		tex_height;
	int		tex_x;
	double	wall_x;
	int		tex_y;
	int		color;
	double	wall_ratio;
	int		tex_width;

	tex_width = 64;
	tex_height = 64;
	line_height = (double)WINDOW_HEIGHT / distance * TILESIZE;
	exact_start = ((double)WINDOW_HEIGHT - line_height) / 2.0;
	exact_end = exact_start + line_height;
	draw_start = (int)(exact_start);
	draw_end = (int)(exact_end + 0.999);
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT;
	switch (game->config.last_wall_hit)
	{
	case 0: // North
		current_texture = game->config.texture_north_img;
		break ;
	case 1: // South
		current_texture = game->config.texture_south_img;
		break ;
	case 2: // West
		current_texture = game->config.texture_west_img;
		break ;
	case 3: // East
		current_texture = game->config.texture_est_img;
		break ;
	default:
		current_texture = game->config.wall;
		break ;
	}
	if (game->config.current_side == 0)
		wall_x = game->config.wall_hit_y;
	else
		wall_x = game->config.wall_hit_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex_width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	draw_line(game, x, 0, x, draw_start, game->config.ceiling_color);
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)(((double)(y - exact_start) / line_height) * tex_height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex_height)
			tex_y = tex_height - 1;
		color = get_texture_pixel(current_texture, tex_x, tex_y, tex_width,
				tex_height);
		wall_ratio = 1.0 - (distance / (TILESIZE * 20));
		if (wall_ratio < 0.3)
			wall_ratio = 0.3;
		color = darken_color(color, wall_ratio);
		put_pixel(game, x, y, color);
		y++;
	}
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

double	cast_ray_dda(t_data *game, double ray_dir_x, double ray_dir_y)
{
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	double	perp_wall_dist;

	hit = 0;
	side = 0;
	map_x = (int)(game->player.pos[0] / TILESIZE);
	map_y = (int)(game->player.pos[1] / TILESIZE);
	game->config.current_ray_dir_x = ray_dir_x;
	game->config.current_ray_dir_y = ray_dir_y;
	if (ray_dir_x == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabs(1 / ray_dir_x);
	if (ray_dir_y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(1 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (game->player.pos[0] / TILESIZE - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->player.pos[0] / TILESIZE)
			* delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (game->player.pos[1] / TILESIZE - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - game->player.pos[1] / TILESIZE)
			* delta_dist_y;
	}
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (map_x < 0 || map_x >= game->map_width || map_y < 0
			|| map_y >= game->map_height || game->map[map_y][map_x] == '1')
		{
			hit = 1;
		}
	}
	game->config.current_side = side;
	if (side == 0)
	{
		if (step_x > 0)
			game->config.last_wall_hit = 2;
		else
			game->config.last_wall_hit = 3;
		perp_wall_dist = (map_x - game->player.pos[0] / TILESIZE + (1 - step_x)
				/ 2) / ray_dir_x;
		game->config.wall_hit_x = game->player.pos[0] / TILESIZE
			+ perp_wall_dist * ray_dir_x;
		game->config.wall_hit_y = map_y;
	}
	else
	{
		if (step_y > 0)
			game->config.last_wall_hit = 0;
		else
			game->config.last_wall_hit = 1;
		perp_wall_dist = (map_y - game->player.pos[1] / TILESIZE + (1 - step_y)
				/ 2) / ray_dir_y;
		game->config.wall_hit_x = map_x;
		game->config.wall_hit_y = game->player.pos[1] / TILESIZE
			+ perp_wall_dist * ray_dir_y;
	}
	return (perp_wall_dist * TILESIZE);
}
