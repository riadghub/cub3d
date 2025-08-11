/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:03:55 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/07 12:19:38 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_side_and_map(t_ray_data *ray, t_point *map_pos, int *side)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		map_pos->x += ray->step_x;
		*side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		map_pos->y += ray->step_y;
		*side = 1;
	}
}

void	perform_dda_loop(t_data *game, t_ray_data *ray, t_point *map_pos)
{
	int	hit;
	int	side;

	hit = 0;
	calculate_step_and_side_dist_x(game, ray);
	calculate_step_and_side_dist_y(game, ray);
	while (hit == 0)
	{
		update_side_and_map(ray, map_pos, &side);
		if (map_pos->x < 0 || map_pos->y < 0 || map_pos->y >= game->map_height)
			hit = 1;
		else if (map_pos->x >= (int)ft_strlen(game->map[map_pos->y]))
			hit = 1;
		else if (game->map[map_pos->y][map_pos->x] == '1')
			hit = 1;
	}
	game->config.current_side = side;
	game->config.step_x = ray->step_x;
	game->config.step_y = ray->step_y;
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
	t_point		map_pos;
	t_ray_data	ray;
	double		perp_wall_dist;

	ray.ray_dir_x = ray_dir_x;
	ray.ray_dir_y = ray_dir_y;
	initialize_ray_data(game, &ray, &map_pos.x, &map_pos.y);
	calculate_delta_distances(&ray);
	perform_dda_loop(game, &ray, &map_pos);
	if (game->config.current_side == 0)
		calculate_wall_hit_and_distance_x(game, map_pos.x, &perp_wall_dist);
	else
		calculate_wall_hit_and_distance_y(game, map_pos.y, &perp_wall_dist);
	return (perp_wall_dist * TILESIZE);
}
