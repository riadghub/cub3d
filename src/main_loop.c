/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:28:02 by lsadi             #+#    #+#             */
/*   Updated: 2025/08/11 12:57:02 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement_keys(t_data *game)
{
	game->player.turndirection = 0;
	game->player.walkdirection = 0;
	if (game->keys[MOVE_UP] || game->keys[ARROW_UP])
		game->player.walkdirection = 1;
	if (game->keys[MOVE_DOWN] || game->keys[ARROW_DOWN])
		game->player.walkdirection = -1;
	if (game->keys[MOVE_LEFT] || game->keys[ARROW_LEFT])
		game->player.turndirection = -1;
	if (game->keys[MOVE_RIGHT] || game->keys[ARROW_RIGHT])
		game->player.turndirection = 1;
}

static void	handle_collision(t_data *game)
{
	if (game->player.walkdirection == 1)
	{
		game->keys[MOVE_UP] = 0;
		game->keys[ARROW_UP] = 0;
	}
	if (game->player.walkdirection == -1)
	{
		game->keys[MOVE_DOWN] = 0;
		game->keys[ARROW_DOWN] = 0;
	}
	if (game->player.turndirection == -1)
	{
		game->keys[MOVE_LEFT] = 0;
		game->keys[ARROW_LEFT] = 0;
	}
	if (game->player.turndirection == 1)
	{
		game->keys[MOVE_RIGHT] = 0;
		game->keys[ARROW_RIGHT] = 0;
	}
}

static void	handle_start_position(t_data *game, double old_x, double old_y)
{
	static bool	at_start = true;

	if (at_start)
	{
		game->player.pos[0] = old_x - game->player.dir[0] * (TILESIZE * 0.1);
		game->player.pos[1] = old_y - game->player.dir[1] * (TILESIZE * 0.1);
		at_start = false;
	}
	else
		handle_collision(game);
}

int	main_loop(t_data *game)
{
	bool	moved;
	double	old_x;
	double	old_y;
	double	dx;
	double	dy;

	handle_movement_keys(game);
	old_x = game->player.pos[0];
	old_y = game->player.pos[1];
	if (game->player.turndirection != 0 || game->player.walkdirection != 0)
		update(game);
	dx = fabs(game->player.pos[0] - old_x);
	dy = fabs(game->player.pos[1] - old_y);
	if (dx > MOVEMENT_THRESHOLD)
		moved = true;
	else if (dy > MOVEMENT_THRESHOLD)
		moved = true;
	else
		moved = false;
	if (!moved)
		handle_start_position(game, old_x, old_y);
	render_map(game);
	usleep(1000);
	return (0);
}
