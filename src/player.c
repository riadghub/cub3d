/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:27:03 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/13 11:45:20 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_player_if_needed(t_data *game)
{
	double	rotation_angle;

	if (game->player.turndirection != 0)
	{
		rotation_angle = game->player.turndirection * 0.03;
		rotate_player(game, rotation_angle);
	}
}

static void	move_forward_backward(t_data *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

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

static void	strafe_left_right(t_data *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.pos[0] + (-game->player.dir[1])
		* (game->player.strafedirection * game->player.movespeed);
	new_y = game->player.pos[1] + game->player.dir[0]
		* (game->player.strafedirection * game->player.movespeed);
	map_x = (int)(new_x / TILESIZE);
	map_y = (int)(new_y / TILESIZE);
	if (!has_wall_at(game, map_x, map_y))
	{
		game->player.pos[0] = new_x;
		game->player.pos[1] = new_y;
	}
}

void	update(t_data *game)
{
	rotate_player_if_needed(game);
	if (game->player.walkdirection != 0)
		move_forward_backward(game);
	if (game->player.strafedirection != 0)
		strafe_left_right(game);
}
