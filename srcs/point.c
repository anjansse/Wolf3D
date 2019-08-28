#include "wolf.h"

int			point_is_wall(t_game *game, t_vector point, int *wall)
{
	int		x;
	int		y;

	x = (int)(point.x / BLOCK_SIZE);
	y = (int)(point.y / BLOCK_SIZE);
	if (0 <= x && x < game->x_max && 0 <= y && y < game->y_max)
	{
		if (game->map[y][x] != 0 && wall)
			*wall = 1;
		return (SUCCESS);
	}
	return (FAILURE);
}

void		point_set(t_vector *point, double x, double y)
{
	point->x = x;
	point->y = y;
}

void		point_update(t_vector *point, double theta, double x, double y)
{
	if (theta <= 90.0 || theta >= 270.0)
		point->x += x;
	else
		point->x -= x;
	if (theta >= 0.0 && theta <= 180.0)
		point->y -= y;
	else
		point->y += y;
}

/* EOF */
