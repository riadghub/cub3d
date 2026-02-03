/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:53:05 by lsadi             #+#    #+#             */
/*   Updated: 2025/08/10 22:53:07 by lsadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config_and_player(t_data *data)
{
	data->config.texture_north = NULL;
	data->config.texture_south = NULL;
	data->config.texture_west = NULL;
	data->config.texture_est = NULL;
	data->config.floor_color = -1;
	data->config.ceiling_color = -1;
	data->config.texture_north_img = NULL;
	data->config.texture_south_img = NULL;
	data->config.texture_west_img = NULL;
	data->config.texture_est_img = NULL;
	data->config.last_wall_hit = 0;
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->player.pos[0] = 0;
	data->player.pos[1] = 0;
	data->player.dir[0] = 0;
	data->player.dir[1] = 0;
	data->player.plane[0] = 0;
	data->player.plane[1] = 0;
	data->player.turndirection = 0;
	data->player.walkdirection = 0;
	data->player.strafedirection = 0;
}

void	init_player_and_keys(t_data *data)
{
	int	i;

	data->player.movespeed = 1.5;
	data->player.rotationspeed = 0.5;
	data->player.direction = '\0';
	data->player.texture_player = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	i = 0;
	while (i < 65536)
	{
		data->keys[i] = 0;
		i++;
	}
}

void	init_data(t_data *data)
{
	init_config_and_player(data);
	init_player_and_keys(data);
}
