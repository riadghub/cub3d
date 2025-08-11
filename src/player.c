/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:27:03 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/07 11:57:37 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	init_player(t_data *game)
// {
// 	game->player.pos[0] = game->player.pos[0] * TILESIZE + TILESIZE / 2;
// 	game->player.pos[1] = game->player.pos[1] * TILESIZE + TILESIZE / 2;
// 	if (game->player.direction == 'N')
// 	{
// 		game->player.dir[0] = 0.0;
// 		game->player.dir[1] = -1.0;
// 	}
// 	else if (game->player.direction == 'S')
// 	{
// 		game->player.dir[0] = 0.0;
// 		game->player.dir[1] = 1.0;
// 	}
// 	else if (game->player.direction == 'E')
// 	{
// 		game->player.dir[0] = 1.0;
// 		game->player.dir[1] = 0.0;
// 	}
// 	else if (game->player.direction == 'W')
// 	{
// 		game->player.dir[0] = -1.0;
// 		game->player.dir[1] = 0.0;
// 	}
// 	game->player.plane[0] = -game->player.dir[1] * 0.66;
// 	game->player.plane[1] = game->player.dir[0] * 0.66;
// 	game->player.turndirection = 0;
// 	game->player.walkdirection = 0;
// 	game->player.movespeed = 1.5;
// 	game->player.rotationspeed = 0.5;
// }

static void	set_player_direction_and_plane(t_data *game)
{
	if (game->player.direction == 'N')
	{
		game->player.dir[0] = 0.0;
		game->player.dir[1] = -1.0;
	}
	else if (game->player.direction == 'S')
	{
		game->player.dir[0] = 0.0;
		game->player.dir[1] = 1.0;
	}
	else if (game->player.direction == 'E')
	{
		game->player.dir[0] = 1.0;
		game->player.dir[1] = 0.0;
	}
	else if (game->player.direction == 'W')
	{
		game->player.dir[0] = -1.0;
		game->player.dir[1] = 0.0;
	}
	game->player.plane[0] = -game->player.dir[1] * 0.66;
	game->player.plane[1] = game->player.dir[0] * 0.66;
}

static void	set_player_movement_params(t_data *game)
{
	game->player.turndirection = 0;
	game->player.walkdirection = 0;
	game->player.movespeed = 1.5;
	game->player.rotationspeed = 0.5;
}

void	init_player(t_data *game)
{
	game->player.pos[0] = game->player.pos[0] * TILESIZE + TILESIZE / 2;
	game->player.pos[1] = game->player.pos[1] * TILESIZE + TILESIZE / 2;
	set_player_direction_and_plane(game);
	set_player_movement_params(game);
}

void	rotate_player(t_data *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	old_dir_x = game->player.dir[0];
	old_plane_x = game->player.plane[0];
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	game->player.dir[0] = old_dir_x * cos_angle - game->player.dir[1]
		* sin_angle;
	game->player.dir[1] = old_dir_x * sin_angle + game->player.dir[1]
		* cos_angle;
	game->player.plane[0] = old_plane_x * cos_angle - game->player.plane[1]
		* sin_angle;
	game->player.plane[1] = old_plane_x * sin_angle + game->player.plane[1]
		* cos_angle;
}

void	update(t_data *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;
	double	rotation_angle;

	if (game->player.turndirection != 0)
	{
		rotation_angle = game->player.turndirection * 0.02;
		rotate_player(game, rotation_angle);
	}
	if (game->player.walkdirection != 0)
	{
		new_x = game->player.pos[0] + game->player.dir[0]
			* (game->player.walkdirection * game->player.movespeed);
		new_y = game->player.pos[1] + game->player.dir[1]
			* (game->player.walkdirection * game->player.movespeed);
		map_x = (int)(new_x / TILESIZE);
		map_y = (int)(new_y / TILESIZE);
		if (!has_wall_at(game, map_x, map_y))
		{
			game->player.pos[0] = new_x;
			game->player.pos[1] = new_y;
		}
	}
}
