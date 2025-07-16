#include "cub3d.h"

#define SIZE2 100

void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX,
		int endY, int color)
{
	int		pixels;
	double	deltaX;
	double	deltaY;
	double	pixelX;
	double	pixelY;

	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(mlx, win, pixelX, pixelY, color);
		// faire fonction au lieu de ca qui ecrit dans data->img
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

double	get_rotation_angleY(t_data *data)
{
	return (sin(data->player.rotationAngle) * SIZE2 + data->player.y);
}

double	get_rotation_angleX(t_data *data)
{
	return (cos(data->player.rotationAngle) * SIZE2 + data->player.x);
}