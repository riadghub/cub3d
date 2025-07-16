/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:33:27 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/16 15:10:45 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_main_image(t_data *game)
{
	game->img = (t_img *)mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (0);
	return (1);
}

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	int		offset;
	char	*pixel;

	if (!img || !img->data || x < 0 || y < 0 || x >= WINDOW_WIDTH
		|| y >= WINDOW_HEIGHT)
		return ;
	offset = (y * img->size_line) + (x * (img->bpp / 8));
	pixel = img->data + offset;
	if (img->bpp == 32)
		*(unsigned int *)pixel = color;
	else if (img->bpp == 24)
	{
		pixel[0] = (color & 0xFF);
		pixel[1] = (color >> 8) & 0xFF;
		pixel[2] = (color >> 16) & 0xFF;
	}
	else if (img->bpp == 16)
		*(unsigned short *)pixel = color;
}

void	put_image_to_image(t_img *dst, t_img *src, int x, int y)
{
	unsigned int	color;

	int i, j;
	int src_offset, dst_offset;
	char *src_pixel, *dst_pixel;
	if (!dst || !src || !dst->data || !src->data)
		return ;
	i = 0;
	while (i < src->height)
	{
		j = 0;
		while (j < src->width)
		{
			if (x + j >= 0 && x + j < dst->width && y + i >= 0 && y
				+ i < dst->height)
			{
				src_offset = (i * src->size_line) + (j * (src->bpp / 8));
				dst_offset = ((y + i) * dst->size_line) + ((x + j) * (dst->bpp
							/ 8));
				src_pixel = src->data + src_offset;
				dst_pixel = dst->data + dst_offset;
				if (src->bpp == 32 && dst->bpp == 32)
				{
					color = *(unsigned int *)src_pixel;
					*(unsigned int *)dst_pixel = color;
				}
				else if (src->bpp == 24 && dst->bpp == 24)
				{
					dst_pixel[0] = src_pixel[0];
					dst_pixel[1] = src_pixel[1];
					dst_pixel[2] = src_pixel[2];
				}
				else if (src->bpp == 16 && dst->bpp == 16)
					*(unsigned short *)dst_pixel = *(unsigned short *)src_pixel;
			}
			j++;
		}
		i++;
	}
}

void	clear_image(t_img *img, int color)
{
	int x, y;
	if (!img || !img->data)
		return ;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_to_image(img, x, y, color);
			x++;
		}
		y++;
	}
}
