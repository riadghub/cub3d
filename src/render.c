#include "cub3d.h"

void	init_size(t_data *game)
{
	int	i;

	i = 0;
	game->map_height = 0;
	game->map_width = 0;
	while (game->map[game->map_width])
		game->map_width++;
	while (game->map[0][i++])
		game->map_height++;
}

int	gamemlx(t_data *game, char *map, char *argv[])
{
	(void)map;
	(void)argv;
	if (!game->mlx)
		return (printf("Error\nFailed to initialize MiniLibX\n"), 0);
	// map = read_map_file(argv[1]);
	// if (!map)
	// 	return (destroy_all(game), ft_printf("Error: Invalid map file\n"), -1);
	// game->map = split_map(map);
	// if (!game->map || !game->map[0] || !is_valid_map(game->map))
	// 	return (destroy_all(game),
	// 		ft_printf("Error: Map is empty or invalid\n"), 0);
	init_size(game);
	// if (!is_map_playable(game))
	// 	return (destroy_all(game), ft_printf("Error: Map isn't playable\n"), 0);
	if (!load_all_textures(game))
	{
		free_textures(game);
		destroy_all(game);
		return (0);
	}
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!game->win)
		return (printf("Error\nFailed to create window\n"), 0);
	return (1);
}

void	rendering(t_data *game, int x, int y)
{
	if (game->map[y][x] == '1')
		put_image_to_image(game->img, (t_img *)game->config.wall, x * TILESIZE,
			y * TILESIZE);
	else if (game->map[y][x] == '0')
		put_image_to_image(game->img, (t_img *)game->config.floor, x * TILESIZE,
			y * TILESIZE);
	put_image_to_image(game->img, (t_img *)game->player.texture_player,
		game->player.x - ((t_img *)game->player.texture_player)->width / 2,
		game->player.y - ((t_img *)game->player.texture_player)->height / 2);
	draw_line(game->img, (int)game->player.x, (int)game->player.y,
		(int)get_rotation_angleX(game), (int)get_rotation_angleY(game),
		0xFF0000);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	render_map(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_width)
	{
		x = 0;
		while (x < game->map_height)
		{
			rendering(game, x, y);
			x++;
		}
		y++;
	}
	render(game->ray);
}

void	destroy_all(t_data *game)
{
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}
