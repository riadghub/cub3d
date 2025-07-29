/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:03:55 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/29 11:41:58 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_side_and_map(double *side_dist_x, double *side_dist_y,
		double delta_dist_x, double delta_dist_y, int *map_x, int *map_y,
		int step_x, int step_y, int *side)
{
	if (*side_dist_x < *side_dist_y)
	{
		*side_dist_x += delta_dist_x;
		*map_x += step_x;
		*side = 0;
	}
	else
	{
		*side_dist_y += delta_dist_y;
		*map_y += step_y;
		*side = 1;
	}
}

void	perform_dda_loop(t_data *game, double delta_dist_x, double delta_dist_y,
		int *map_x, int *map_y)
{
	int		hit;
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;

	hit = 0;
	calculate_step_and_side_dist_x(game, game->config.current_ray_dir_x,
		delta_dist_x, &step_x, &side_dist_x);
	calculate_step_and_side_dist_y(game, game->config.current_ray_dir_y,
		delta_dist_y, &game->config.step_y, &side_dist_y);
	while (hit == 0)
	{
		update_side_and_map(&side_dist_x, &side_dist_y, delta_dist_x,
			delta_dist_y, map_x, map_y, step_x, game->config.step_y, &side);
		if (*map_x < 0 || *map_x >= game->map_width || *map_y < 0
			|| *map_y >= game->map_height || game->map[*map_y][*map_x] == '1')
			hit = 1;
	}
	game->config.current_side = side;
	game->config.step_x = step_x;
}

void	calculate_wall_hit_and_distance_x(t_data *game, int map_x,
		double *perp_wall_dist)
{
	if (game->config.step_x > 0)
		game->config.last_wall_hit = 2;
	else
		game->config.last_wall_hit = 3;
	*perp_wall_dist = (map_x - game->player.pos[0] / TILESIZE + (1
				- game->config.step_x) / 2) / game->config.current_ray_dir_x;
	game->config.wall_hit_x = game->player.pos[0] / TILESIZE + *perp_wall_dist
		* game->config.current_ray_dir_x;
	game->config.wall_hit_y = (int)(game->player.pos[1] / TILESIZE);
}

void	calculate_wall_hit_and_distance_y(t_data *game, int map_y,
		double *perp_wall_dist)
{
	if (game->config.step_y > 0)
		game->config.last_wall_hit = 0;
	else
		game->config.last_wall_hit = 1;
	*perp_wall_dist = (map_y - game->player.pos[1] / TILESIZE + (1
				- game->config.step_y) / 2) / game->config.current_ray_dir_y;
	game->config.wall_hit_x = (int)(game->player.pos[0] / TILESIZE);
	game->config.wall_hit_y = game->player.pos[1] / TILESIZE + *perp_wall_dist
		* game->config.current_ray_dir_y;
}

double	cast_ray_dda(t_data *game, double ray_dir_x, double ray_dir_y)
{
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;

	initialize_ray_data(game, ray_dir_x, ray_dir_y, &map_x, &map_y);
	calculate_delta_distances(ray_dir_x, ray_dir_y, &delta_dist_x,
		&delta_dist_y);
	perform_dda_loop(game, delta_dist_x, delta_dist_y, &map_x, &map_y);
	if (game->config.current_side == 0)
		calculate_wall_hit_and_distance_x(game, map_x, &perp_wall_dist);
	else
		calculate_wall_hit_and_distance_y(game, map_y, &perp_wall_dist);
	return (perp_wall_dist * TILESIZE);
}
