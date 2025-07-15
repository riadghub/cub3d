/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:23:57 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/15 15:29:34 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *game)
{
	game->player.x = WINDOW_WIDTH / 2;
	game->player.y = WINDOW_HEIGHT / 2;
	game->player.turnDirection = 0;
	game->player.moveSpeed = 4;
	game->player.rotationSpeed = 0.1;
	game->player.rotationAngle = 0;
}

void	update(int key, t_data *game)
{
	int	moveStep;

	game->player.turnDirection = 0;
	game->player.walkDirection = 0;
	if (key == MOVE_RIGHT)
		game->player.turnDirection = 1;
	if (key == MOVE_LEFT)
		game->player.turnDirection = -1;
	if (key == MOVE_UP)
		game->player.walkDirection = 1;
	if (key == MOVE_DOWN)
		game->player.walkDirection = -1;
	moveStep = game->player.walkDirection * game->player.moveSpeed;
	game->player.rotationAngle += game->player.turnDirection
		* game->player.rotationSpeed;
	game->player.x += cos(game->player.rotationAngle) * moveStep;
	game->player.y += sin(game->player.rotationAngle) * moveStep;
}
