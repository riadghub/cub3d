/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:33:27 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/08/07 11:29:46 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_data *game, int x, int y, int color)
{
	char	*dst;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = mlx_get_data_addr(game->img, &bits_per_pixel, &line_length, &endian);
	dst += (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	blend_colors(int color1, int color2, double alpha)
{
	int	r;
	int	g;
	int	b;
	int	temp;
	int	result;

	r = (color1 >> 16) & 0xFF;
	g = (color1 >> 8) & 0xFF;
	b = color1 & 0xFF;
	temp = (color2 >> 16) & 0xFF;
	r = (int)(r * (1 - alpha) + temp * alpha);
	temp = (color2 >> 8) & 0xFF;
	g = (int)(g * (1 - alpha) + temp * alpha);
	temp = color2 & 0xFF;
	b = (int)(b * (1 - alpha) + temp * alpha);
	result = (r << 16) | (g << 8) | b;
	return (result);
}

int	darken_color(int original_color, double ratio)
{
	int	r;
	int	g;
	int	b;

	r = ((original_color >> 16) & 0xFF) * ratio;
	g = ((original_color >> 8) & 0xFF) * ratio;
	b = (original_color & 0xFF) * ratio;
	return ((r << 16) | (g << 8) | b);
}

int	get_texture_pixel(void *texture, t_point coord, int tex_width,
		int tex_height)
{
	char	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		*pixel_ptr;

	if (!texture || coord.x < 0 || coord.x >= tex_width || coord.y < 0
		|| coord.y >= tex_height)
		return (0x000000);
	data = mlx_get_data_addr(texture, &bits_per_pixel, &line_length, &endian);
	pixel_ptr = (int *)(data + (coord.y * line_length + coord.x
				* (bits_per_pixel / 8)));
	return (*pixel_ptr);
}
