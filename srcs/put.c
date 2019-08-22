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

void		put_pixel(t_game game, t_vector p, int color)
{
	game.pixels[((int)round(p.y) * SCREEN_WIDTH) + (int)round(p.x)] = color;
}

void		put_line(t_game game, t_vector p, size_t size, int color)
{
	while (size)
	{
		put_pixel(game, p, color);
		++p.y;
		--size;
	}
}

/* EOF */
