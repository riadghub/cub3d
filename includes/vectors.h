/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:40:08 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/15 13:48:53 by reeer-aa         ###   ########.fr       */
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

void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX,
			int endY, int color);
void	update(int key, t_data *game);
double	get_rotation_angleY(t_data *data);
double	get_rotation_angleX(t_data *data);

#endif