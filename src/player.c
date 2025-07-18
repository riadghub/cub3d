/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:27:03 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/16 12:11:17 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *game)
{
	// Utiliser la position trouvée dans la carte !
	game->player.x = game->player.x * TILESIZE + TILESIZE / 2;
	// // Convertir en pixels
	game->player.y = game->player.y * TILESIZE + TILESIZE / 2;
	// Centre de la case
	game->player.turnDirection = 0;
	game->player.moveSpeed = 4;
	game->player.rotationSpeed = 0.1;
	game->player.rotationAngle = 0;
	if (game->player.direction == 'N')
		game->player.rotationAngle = -M_PI / 2; // Nord = -90°
	else if (game->player.direction == 'S')
		game->player.rotationAngle = M_PI / 2; // Sud = 90°
	else if (game->player.direction == 'E')
		game->player.rotationAngle = 0; // Est = 0°
	else if (game->player.direction == 'W')
		game->player.rotationAngle = M_PI; // Ouest = 180°
}

// void	update(int key, t_data *game)
// {
// 	int	moveStep;

// 	game->player.turnDirection = 0;
// 	game->player.walkDirection = 0;
// 	if (key == MOVE_RIGHT)
// 		game->player.turnDirection = 1;
// 	if (key == MOVE_LEFT)
// 		game->player.turnDirection = -1;
// 	if (key == MOVE_UP)
// 		game->player.walkDirection = 1;
// 	if (key == MOVE_DOWN)
// 		game->player.walkDirection = -1;
// 	moveStep = game->player.walkDirection * game->player.moveSpeed;
// 	game->player.rotationAngle += game->player.turnDirection
// 		* game->player.rotationSpeed;
// 	game->player.x += cos(game->player.rotationAngle) * moveStep;
// 	game->player.y += sin(game->player.rotationAngle) * moveStep;
// }

void	update(int key, t_data *game)
{
	int		moveStep;
	double	newX;
	double	newY;
	int		mapX;
	int		mapY;

	game->player.turnDirection = 0;
	game->player.walkDirection = 0;
	if (key == MOVE_RIGHT || key == ARROW_RIGHT)
		game->player.turnDirection = 1;
	if (key == MOVE_LEFT || key == ARROW_LEFT)
		game->player.turnDirection = -1;
	if (key == MOVE_UP || key == ARROW_UP)
		game->player.walkDirection = 1;
	if (key == MOVE_DOWN || key == ARROW_DOWN)
		game->player.walkDirection = -1;
	moveStep = game->player.walkDirection * game->player.moveSpeed;
	game->player.rotationAngle += game->player.turnDirection
		* game->player.rotationSpeed;
	newX = game->player.x + cos(game->player.rotationAngle) * moveStep;
	newY = game->player.y + sin(game->player.rotationAngle) * moveStep;
	mapX = (int)(newX / TILESIZE);
	mapY = (int)(newY / TILESIZE);
	if (!has_wall_at(game, mapX, mapY))
	{
		game->player.x = newX;
		game->player.y = newY;
	}
}
