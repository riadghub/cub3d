/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:30:05 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/07 11:25:34 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *game)
{
	if (key == 65307)
		close_game(game);
	if (key >= 0 && key < 65536)
		game->keys[key] = 1;
	return (0);
}

int	key_release(int key, t_data *game)
{
	if (key >= 0 && key < 65536)
		game->keys[key] = 0;
	return (0);
}

int	close_game(t_data *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}
