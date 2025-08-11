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

static int	setup_mlx_and_game(t_data *data, char *map, char **av)
{
	int	r;

	data->mlx = mlx_init();
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->mlx)
	{
		cleanup_data(data);
		return (printf("Mlx failed to create\n"), 1);
	}
	r = gamemlx(data, map, av);
	if (r != 1)
	{
		cleanup_data(data);
		return (1);
	}
	render_map(data);
	mlx_hook(data->win, 17, 0, close_game, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx, main_loop, data);
	mlx_loop(data->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	*map;
	int		result;

	map = NULL;
	if (initialize_and_validate(ac, av, &data))
		return (1);
	result = setup_mlx_and_game(&data, map, av);
	cleanup_data(&data);
	return (result);
}
