/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:45:47 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/07 11:59:52 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_config_and_player(t_data *data)
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
	data->player.turnDirection = 0;
	data->player.walkDirection = 0;
}

static void	init_player_and_keys(t_data *data)
{
	int	i;

	data->player.moveSpeed = 0.5;
	data->player.rotationSpeed = 0.5;
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

static int	initialize_and_validate(int ac, char **av, t_data *data)
{
	if (ac != 2 || !check_file_extension(av[1]))
		return (printf("usage: %s <map.cub>\n", av[0]), 1);
	init_data(data);
	if (parse_file(av[1], data))
	{
		cleanup_data(data);
		return (1);
	}
	if (!check_map(data))
	{
		free_texture_paths(data);
		cleanup_data(data);
		return (1);
	}
	printf("Carte valide !\n");
	init_player(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	*map;
	int		r;

	map = NULL;
	if (initialize_and_validate(ac, av, &data))
		return (1);
	data.mlx = mlx_init();
	data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data.mlx)
	{
		cleanup_data(&data);
		return (printf("Mlx failed to create\n"), 1);
	}
	r = gamemlx(&data, map, av);
	if (r != 1)
	{
		cleanup_data(&data);
		return (1);
	}
	render_map(&data);
	mlx_hook(data.win, 17, 0, close_game, &data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_loop(data.mlx);
	cleanup_data(&data);
	return (0);
}
