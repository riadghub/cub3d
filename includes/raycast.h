/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:29:54 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/25 14:12:11 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3d.h"
# include "mlx_int.h"
# include <math.h>

# define SIZE2 100
# define TILESIZE 48
# define ROWS 10
# define COLS 15
# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 720
# define D WINDOW_WIDTH / (tan(30))
# define FOV 60 * (M_PI / 180)
# define RES 1
# define NUM_RAYS (WINDOW_WIDTH * 4)
# define WALL_PATH "textures/wall.xpm"
# define FLOOR_PATH "textures/tile.xpm"
# define PLAYER_PATH "textures/red_dot.xpm"
# define MINIMAP_SIZE 160
# define MINIMAP_TILE_SIZE 20
# define MINIMAP_MARGIN 20
# define MINIMAP_PLAYER_SIZE 10
# define MINIMAP_VIEW_RADIUS 10

typedef struct s_data	t_data;

int						close_game(t_data *game);
int						has_wall_at(t_data *game, int x, int y);
int						handle_input(int key, t_data *game);
int						gamemlx(t_data *game, char *map, char *argv[]);
int						load_all_textures(t_data *game);
void					destroy_all(t_data *game);
void					free_textures(t_data *game);
void					init_player(t_data *game);
void					*load_texture(void *mlx, char *path);
void					rendering(t_data *game, int x);
void					render_map(t_data *game);
void					initialize_ray_data(t_data *game, double ray_dir_x,
							double ray_dir_y, int *map_x, int *map_y);
void					calculate_delta_distances(double ray_dir_x,
							double ray_dir_y, double *delta_dist_x,
							double *delta_dist_y);
void					calculate_step_and_side_dist_x(t_data *game,
							double ray_dir_x, double delta_dist_x, int *step_x,
							double *side_dist_x);
void					calculate_step_and_side_dist_y(t_data *game,
							double ray_dir_y, double delta_dist_y, int *step_y,
							double *side_dist_y);
int						blend_colors(int color1, int color2, double alpha);
int						get_texture_pixel(void *texture, int x, int y,
							int tex_width, int tex_height);
void					draw_wall_column(t_data *game, int x, double distance);
void					render(t_data *game);
void					render_minimap(t_data *game);
double					cast_ray_dda(t_data *game, double ray_dir_x,
							double ray_dir_y);
void					put_pixel(t_data *game, int x, int y, int color);
int						blend_colors(int color1, int color2, double alpha);
void					render_map(t_data *game);
int						darken_color(int original_color, double ratio);
void					draw_wall_pixels(t_data *game, int x, void *texture,
							int draw_start, int draw_end);
void					calculate_draw_bounds(double distance, int *draw_start,
							int *draw_end);
void					select_wall_texture(t_data *game,
							void **current_texture);
void					calculate_texture_x(t_data *game, int *tex_x,
							int tex_width);
void					calculate_texture_y_and_color(t_data *game,
							void *texture, int tex_x, int y, int *color);
void					update_side_and_map(double *side_dist_x,
							double *side_dist_y, double delta_dist_x,
							double delta_dist_y, int *map_x, int *map_y,
							int step_x, int step_y, int *side);
void					perform_dda_loop(t_data *game, double delta_dist_x,
							double delta_dist_y, int *map_x, int *map_y);
void					calculate_wall_hit_and_distance_x(t_data *game,
							int map_x, double *perp_wall_dist);
void					calculate_wall_hit_and_distance_y(t_data *game,
							int map_y, double *perp_wall_dist);
int						init_main_image(t_data *game);
void					put_pixel_to_image(t_img *img, int x, int y, int color);
void					put_image_to_image(t_img *dst, t_img *src, int x,
							int y);

#endif