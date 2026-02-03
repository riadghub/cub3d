/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:09:16 by lsadi             #+#    #+#             */
/*   Updated: 2025/08/18 12:09:20 by lsadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mouse(t_data *game)
{
	game->mouse.center_x = WINDOW_WIDTH / 2;
	game->mouse.center_y = WINDOW_HEIGHT / 2;
	game->mouse.sensitivity = 0.002;
	game->mouse.is_captured = 1;
	game->mouse.last_x = game->mouse.center_x;
	game->mouse.last_y = game->mouse.center_y;
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, game->mouse.center_x,
		game->mouse.center_y);
}

int	mouse_move(int x, int y, t_data *game)
{
	double	rotation_angle;
	int		delta_x;
	int		delta_y;

	if (!game->mouse.is_captured)
		return (0);
	delta_x = x - game->mouse.center_x;
	delta_y = y - game->mouse.center_y;
	if (abs(delta_x) < 2 && abs(delta_y) < 2)
		return (0);
	if (delta_x != 0)
	{
		rotation_angle = delta_x * game->mouse.sensitivity;
		rotate_player(game, rotation_angle);
	}
	mlx_mouse_move(game->mlx, game->win, game->mouse.center_x,
		game->mouse.center_y);
	return (0);
}
