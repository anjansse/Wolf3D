#include "wolf.h"

void		put_background(t_game *game, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (i < size / 2)
			game->pixels[i] = SKY;
		else
			game->pixels[i] = FLOOR;
		++i;
	}
}

void		put_pixel(t_game *game, t_point point, int color)
{
	game->pixels[point.y * SCREEN_WIDTH + point.x] = color;
}

void		put_column(t_game *game, t_point point, size_t size, int color)
{
	size_t 		tmp;
	t_point		up_point;

	tmp = size / 2;
	point.y = SCREEN_HEIGTH / 2;
	up_point = point;
	while (tmp)
	{
		put_pixel(game, point, color);
		put_pixel(game, up_point, color);
		point.y = (point.y + 1 >= SCREEN_HEIGTH) ? SCREEN_HEIGTH - 1: point.y + 1;
		up_point.y = (up_point.y - 1 <= 0) ? 0 : up_point.y - 1;
		--tmp;
	}
}
/* EOF */
