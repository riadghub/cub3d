/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:29:54 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/13 15:18:50 by reeer-aa         ###   ########.fr       */
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
# define MOVEMENT_THRESHOLD 1e-6
// # define D WINDOW_WIDTH / (tan(30))
// # define FOV 60 * (M_PI / 180)
// # define NUM_RAYS (WINDOW_WIDTH * 4)
# define D 62.35
# define FOV 1.047197551
# define RES 1
# define NUM_RAYS 4320
# define WALL_PATH "textures/wall.xpm"
# define FLOOR_PATH "textures/tile.xpm"
# define PLAYER_PATH "textures/red_dot.xpm"

// ===== CONSTANTESMINIMAP =====
# define MINIMAP_SIZE 200      // taille
# define MINIMAP_TILE_SIZE 15  // Tiles fines pour précision
# define MINIMAP_PLAYER_SIZE 7 // Joueur
# define MINIMAP_BORDER_SIZE 2 // Bordure fine
# define MINIMAP_MARGIN 20     // Marge depuis les bords de l'écran
# define MINIMAP_ALPHA 0.85    // Transparence
# define MINIMAP_MARGIN 20

// Couleurs modernes et contrastées
# define COLOR_MINIMAP_BG 0x1a1a1a     // Fond sombre
# define COLOR_MINIMAP_BORDER 0x4a4a4a // Bordure gris foncé
# define COLOR_WALL 0x606060           // Murs gris moyen
# define COLOR_FLOOR 0xf0f0f0          // Sol blanc cassé
# define COLOR_VOID 0x2a2a2a           // Vide gris très foncé
# define COLOR_PLAYER 0xff6b35         // Orange vif pour le joueur
# define COLOR_DIRECTION 0xff9500      // Orange clair pour la direction
# define COLOR_FOV_LINE 0x3366cc       // Bleu pour les lignes de FOV

typedef struct s_data		t_data;
typedef struct s_ray_data	t_ray_data;
typedef struct s_point		t_point;

int							close_game(t_data *game);
int							has_wall_at(t_data *game, int x, int y);

int							key_press(int key, t_data *game);
int							key_release(int key, t_data *game);

int							gamemlx(t_data *game, char *map, char *argv[]);
int							load_all_textures(t_data *game);
void						destroy_all(t_data *game);
void						free_textures(t_data *game);
void						free_texture_paths(t_data *data);

void						init_player(t_data *game);
void						*load_texture(void *mlx, char *path);
void						render_map(t_data *game);
void						initialize_ray_data(t_data *game, t_ray_data *ray,
								int *map_x, int *map_y);
void						calculate_delta_distances(t_ray_data *ray);
void						calculate_step_and_side_dist_x(t_data *game,
								t_ray_data *ray);
void						calculate_step_and_side_dist_y(t_data *game,
								t_ray_data *ray);
int							blend_colors(int color1, int color2, double alpha);
int							get_texture_pixel(void *texture, t_point coord,
								int tex_width, int tex_height);
void						draw_wall_column(t_data *game, int x,
								double distance);
void						render(t_data *game);
void						render_minimap(t_data *game);
double						cast_ray_dda(t_data *game, double ray_dir_x,
								double ray_dir_y);
void						put_pixel(t_data *game, int x, int y, int color);
int							blend_colors(int color1, int color2, double alpha);
void						render_map(t_data *game);
int							darken_color(int original_color, double ratio);
void						draw_wall_pixels(t_data *game, int x, void *texture,
								t_point bounds);
void						calculate_draw_bounds(double distance,
								int *draw_start, int *draw_end);
void						select_wall_texture(t_data *game,
								void **current_texture);
void						calculate_texture_x(t_data *game, int *tex_x,
								int tex_width);
void						calculate_texture_y_and_color(t_data *game,
								void *texture, t_point pos, int *color);
void						update_side_and_map(t_ray_data *ray,
								t_point *map_pos, int *side);
void						perform_dda_loop(t_data *game, t_ray_data *ray,
								t_point *map_pos);
void						calculate_wall_hit_and_distance_x(t_data *game,
								int map_x, double *perp_wall_dist);
void						calculate_wall_hit_and_distance_y(t_data *game,
								int map_y, double *perp_wall_dist);
int							get_modern_tile_color(char tile);
int							is_pixel_in_minimap_bounds(int pixel_x,
								int pixel_y);
void						draw_circle_pixel(t_data *game, t_point center,
								t_point offset, int color);
void						draw_circle(t_data *game, t_point center,
								int radius, int color);
t_point						calculate_border_distance(t_point pos,
								t_point start);
void						draw_minimap_border(t_data *game, t_point start);
void						draw_minimap_background(t_data *game,
								t_point start);
void						draw_modern_minimap_background(t_data *game);
int							get_wall_pixel_color(int x, int y, int color);
void						draw_tile_pixel(t_data *game, t_point screen_pos,
								t_point offset, int color);
void						draw_smooth_tile(t_data *game, t_point screen_pos,
								int color);
void						calculate_map_position(t_data *game, int minimap_x,
								int minimap_y, t_point *map_pos);
void						draw_minimap_tile(t_data *game, t_point minimap_pos,
								t_point map_pos);
void						draw_single_fov_line(t_data *game, t_point center,
								int direction);
void						draw_fov_lines(t_data *game, int center_x,
								int center_y);
void						draw_player_direction(t_data *game, int center_x,
								int center_y);
void						draw_modern_player(t_data *game);
void						render_precise_tiles(t_data *game);
double						calculate_fov_angle(t_data *game, int direction);

#endif