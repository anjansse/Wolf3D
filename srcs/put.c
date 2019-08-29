#include "wolf.h"

void		put_background(t_game game, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (i < size / 2)
			game.pixels[i] = SKY;
		else
			game.pixels[i] = FLOOR;
		++i;
	}
}

void		put_pixel(t_game *game, t_vector point, int color)
{
	game->pixels[((int)round(point.y) * SCREEN_WIDTH) + (int)round(point.x)] = color;
}


void		put_column(t_game *game, t_vector point, size_t size, int color)
{
	size_t tmp;

	tmp = size / 2;
	point.y = SCREEN_HEIGTH / 2;
	while (tmp)
	{
		put_pixel(game, point, color);
		point.y = (point);
		--tmp;
	}
	tmp = size / 2;
	point.y = SCREEN_HEIGTH / 2;
	while (tmp)
	{
		put_pixel(game, point, color);
		--point.y;
		--tmp;
	}
}

/* EOF */
