/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:41:33 by lsadi             #+#    #+#             */
/*   Updated: 2025/07/15 14:10:00 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "raycast.h"
# include "vectors.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define EQUAL =

typedef struct s_config
{
	void		*wall;
	void		*floor;
	char		*texture_north;
	char		*texture_south;
	char		*texture_west;
	char		*texture_est;
	int			floor_color;
	int			ceiling_color;
}				t_config;

typedef struct s_player
{
	double		x;
	double		y;
	int			turnDirection;
	int			walkDirection;
	double		rotationSpeed;
	double		rotationAngle;
	double		moveSpeed;
	char direction; // N, S, E, W
	char		*texture_player;
}				t_player;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_config	config;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
}				t_data;

// ========== FONCTIONS DE PARSING ==========
int				parse_file(const char *filename, t_data *data);
void			parse_color_line(char *line, t_config *config);
void			parse_texture_line(char *line, t_config *config);
int				is_color_line(char *line);
int				is_texture_line(char *line);
int				is_map_line(char *line);

// ========== FONCTIONS DE GESTION DE CARTE ==========
void			add_map_line(t_data *data, char *line);
void			cleanup_map(t_data *data);
int				find_player(t_data *data);
void			print_map(t_data *data);

// ========== FONCTIONS DE VALIDATION ==========
int				check_walls(t_data *data);
int				check_spaces(t_data *data);
int				check_path(t_data *data);
int				check_files(t_config *config);
int				check_map(t_data *data);
int				check_content(t_data *data);

// ========== FONCTIONS PRINCIPALES ==========
void			init_data(t_data *data);
void			init_size(t_data *s_data);
void			print_config(t_config *config);
void			cleanup_data(t_data *data);
int				check_file_extension(char *filename);

// Validation des bordures
int				check_line(t_data *data, int line_index);
int				check_sides(t_data *data, int i);
int				check_walls(t_data *data);

// ==========

// int				is_valid_wall(t_data *data);
// int				is_valid_content(t_data *data);
// int				is_valid_map(t_data *data);

// Validation des espaces
int				check_pos(t_data *data, int x, int y);
int				check_around(t_data *data, int x, int y);
int				check_spaces(t_data *data);

// Flood fill algorithm
int				is_border(t_data *data, int x, int y);
void			flood_fill(char **map, int x, int y, t_data *data, int *valid);
char			**copy_map(t_data *data);
void			free_copy(char **map, int height);
int				check_path(t_data *data);

// Validation des fichiers
int				file_exists(char *filename);
int				check_files(t_config *config);

// Validation principale
int				check_map(t_data *data);

// int				parse_file(const char *filename, t_data *data);
// void			parse_color_line(char *line, t_config *config);
// void			parse_texture_line(char *line, t_config *config);
// int				is_color_line(char *line);
// int				is_texture_line(char *line);
// int				is_map_line(char *line);
// void			cleanup_config(t_config *config);
// void			cleanup_data(t_data *data);

// void			add_map_line(t_data *data, char *line);
// void			cleanup_map(t_data *data);
// int				find_player(t_data *data);
// void			print_map(t_data *data);
// int				check_file_extension(char *filename);
// int				is_valid_wall(t_data *data);
// int				is_valid_content(t_data *data);
// int				is_valid_map(t_data *data);
// int				ft_tablen(char **str);

#endif
