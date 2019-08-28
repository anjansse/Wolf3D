#include "wolf.h"

static int		point_is_wall(t_game *game, t_vector point, int *wall)
{
	int		x;
	int		y;

	x = (int)(point.x / BLOCK_SIZE);
	y = (int)(point.y / BLOCK_SIZE);
	printf("%d | %d\n", x, y);
	if (0 <= x && x < game->x_max && 0 <= y && y < game->y_max)
	{
		if (game->map[y][x] != 0 && wall)
			*wall = 1;
		return (SUCCESS);
	}
	return (FAILURE);
}

static double	checking_horizontal(t_game *game, double theta)
{
	int			wall;
	double		x;
	double		y;
	t_vector	point;

	wall = 0;
	x = fabs((BLOCK_SIZE / 2) / tan(theta * (M_PI / 180)));
	y = BLOCK_SIZE / 2;
	point.x = (theta <= 90.0 || theta >= 270.0) ? game->bob.position.x + x : game->bob.position.x - x;
	point.y = (theta >= 0.0 && theta <= 180.0) ? game->bob.position.y - y : game->bob.position.y + y;

	x = fabs(BLOCK_SIZE / tan(theta * (M_PI / 180)));
	x = (theta <= 90.0 || theta >= 270.0) ? x : -x;
	y = (theta >= 0.0 && theta <= 180.0) ? -BLOCK_SIZE : BLOCK_SIZE;
	while (SUCCESS == point_is_wall(game, point, &wall) && wall == 0)
	{
		point.x += x;
		point.y += y;
	}
	if (wall == 0)
		return (MAXFLOAT);
	return (sqrt(pow(point.x - game->bob.position.x, 2) + pow(point.y - game->bob.position.y, 2)));
}

static double	checking_vertical(t_game *game, double theta)
{
	int			wall;
	double		x;
	double		y;
	t_vector	point;

	wall = 0;
	x = BLOCK_SIZE / 2;
	y = fabs((BLOCK_SIZE / 2) * tan(theta * (M_PI / 180)));
	point.x = (theta <= 90.0 || theta >= 270.0) ? game->bob.position.x + x : game->bob.position.x - x;
	point.y = (theta >= 0.0 && theta <= 180.0) ? game->bob.position.y - y : game->bob.position.y + y;

	y = fabs(BLOCK_SIZE * tan(theta * (M_PI / 180)));
	x = (theta <= 90.0 || theta >= 270.0) ? BLOCK_SIZE : -BLOCK_SIZE;
	y = (theta >= 0.0 && theta <= 180.0) ? -y : y;
	while (SUCCESS == point_is_wall(game, point, &wall) && wall == 0)
	{
		point.x += x;
		point.y += y;
	}
	if (wall == 0)
		return (MAXFLOAT);
	return (sqrt(pow(point.x - game->bob.position.x, 2) + pow(point.y - game->bob.position.y, 2)));
}

static double	checking_execption(t_game *game, double theta)
{
	int			wall;
	t_vector	point;

	wall = 0;
	point.x = game->bob.position.x;
	point.y = game->bob.position.y;
	if (theta == 0.0 || theta == 180.0)
	{
		while (SUCCESS == point_is_wall(game, point, &wall) && wall == 0)
			point.x += (theta == 0.0) ? BLOCK_SIZE : -BLOCK_SIZE;
		if (wall == 0)
			return (MAXFLOAT);
		return (fabs(game->bob.position.x - point.x) - 3 * BLOCK_SIZE / 2);
	}
	else
	{
		while (SUCCESS == point_is_wall(game, point, &wall) && wall == 0)
			point.y += (theta == 90.0) ? -BLOCK_SIZE : BLOCK_SIZE;
		if (wall == 0)
			return (MAXFLOAT);
		return (fabs(game->bob.position.y - point.y) - 3 * BLOCK_SIZE / 2);
	}
}

double			distance_wall(t_game *game, double theta)
{
	double	vertical;
	double	horizontal;

	if (theta == 0.0 || theta == 90.0 || theta == 180.0 || theta == 270.0)
		return (checking_execption(game, theta));
	horizontal = checking_horizontal(game, theta);
	printf("\n");
	vertical = checking_vertical(game, theta);
	printf("\n%f | %f\n", horizontal, vertical);
	return ((vertical < horizontal) ? vertical : horizontal);
}

/* EOF */
