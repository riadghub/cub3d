/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:30:05 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/19 10:21:52 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_special_keys(int key, t_data *game)
{
	printf("%d", key);
	if (key == 53)
	{
		if (game->mouse.is_captured)
		{
			game->mouse.is_captured = 0;
			mlx_mouse_show(game->mlx, game->win);
		}
		else
			close_game(game);
	}
	if (key == 65289)
	{
		game->mouse.is_captured = !game->mouse.is_captured;
		if (game->mouse.is_captured)
		{
			mlx_mouse_hide(game->mlx, game->win);
			mlx_mouse_move(game->mlx, game->win, game->mouse.center_x,
				game->mouse.center_y);
		}
		else
			mlx_mouse_show(game->mlx, game->win);
	}
}

int	key_press(int key, t_data *game)
{
	if (key == 65307)
		close_game(game);
	if (key >= 0 && key < 65536)
		game->keys[key] = 1;
	handle_special_keys(key, game);
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
