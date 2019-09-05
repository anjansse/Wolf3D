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

// static int		get_text_coord(t_game *game, t_point *point)
// {
// 	int		max;
// 	int		n;

// 	max = floor(game->size / 64);
// 	n = 1 + floor(point->y / max);
// 	if ((point->y % max) == 0)
// 		return ((n + 1 * 64) + point->x);
// 	return ((n * 64) + point->x);
// }

void		put_pixel(t_game *game, t_point point, int color)
{
	(void)color;
	// printf("res: %d\t", point.y * SCREEN_WIDTH + point.x);
	// game->pixels[point.y * SCREEN_WIDTH + point.x] = game->textures[0][get_text_coord(game, &point) % 4096];
	game->pixels[point.y * SCREEN_WIDTH + point.x] = color;
}

void		put_column(t_game *game, t_point point, size_t size, int color)
{
	size_t 		tmp;
	t_point		up_point;

	game->size = size;
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
