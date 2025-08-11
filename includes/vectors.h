/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:39:32 by lsadi             #+#    #+#             */
/*   Updated: 2025/08/10 20:39:34 by lsadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include "cub3d.h"
# include <math.h>

# define MOVE_UP 'w'
# define MOVE_DOWN 's'
# define MOVE_LEFT 'a'
# define MOVE_RIGHT 'd'
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define ESC_KEY 65307

void	draw_line(t_data *game, t_point begin, t_point end, int color);
void	update(t_data *game);
void	rotate_player(t_data *game, double angle);

double	get_rotation_angle_y(t_data *data);
double	get_rotation_angle_x(t_data *data);

#endif
