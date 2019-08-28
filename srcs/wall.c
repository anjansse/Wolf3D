#include "wolf.h"

static double	wall_execption(t_game *game, t_vector player, double theta)
{
	int			wall;
	t_vector	point;

	wall = 0;
	point_set(&point, player.x, player.y);
	if (theta == 0.0 || theta == 180.0)
	{
		while (SUCCESS == point_is_wall(game, point, &wall) && wall == 0)
			point.x += (theta == 0.0) ? BLOCK_SIZE : -BLOCK_SIZE;
		if (wall == 0)
			return (MAXFLOAT);
		return (fabs(player.x - point.x) - BLOCK_SIZE / 2);
	}
	else
	{
		while (SUCCESS == point_is_wall(game, point, &wall) && wall == 0)
			point.y += (theta == 90.0) ? -BLOCK_SIZE : BLOCK_SIZE;
		if (wall == 0)
			return (MAXFLOAT);
		return (fabs(player.y - point.y) - BLOCK_SIZE / 2);
	}
}

static double	wall_horizontal(t_game *game, t_vector player, double theta)
{
	int			wall;
	double		x;
	t_vector	point;

	wall = 0;
	point_set(&point, player.x, player.y);
	x = fabs((BLOCK_SIZE / 2) / tan(theta * (M_PI / 180)));
	point_update(&point, theta, x, BLOCK_SIZE / 2);
	x = fabs(BLOCK_SIZE / tan(theta * (M_PI / 180))) + 1.0;
	while (SUCCESS == point_is_wall(game, point, &wall) && wall == 0)
		point_update(&point, theta, x, BLOCK_SIZE + 1.0);
	if (wall == 0)
		return (MAXFLOAT);
	return (sqrt(pow(point.x - player.x, 2) + pow(point.y - player.y, 2)));
}

static double	wall_vertical(t_game *game, t_vector player, double theta)
{
	int			wall;
	double		y;
	t_vector	point;

	wall = 0;
	point_set(&point, player.x, player.y);
	y = fabs((BLOCK_SIZE / 2) * tan(theta * (M_PI / 180)));
	point_update(&point, theta, BLOCK_SIZE / 2, y);
	y = fabs(BLOCK_SIZE * tan(theta * (M_PI / 180))) + 1.0;
	while (SUCCESS == point_is_wall(game, point, &wall) && wall == 0)
		point_update(&point, theta, BLOCK_SIZE + 1.0, y);
	if (wall == 0)
		return (MAXFLOAT);
	return (sqrt(pow(point.x - player.x, 2) + pow(point.y - player.y, 2)));
}

double			distance_wall(t_game *game, double theta)
{
	double		vertical;
	double		horizontal;
	t_vector	player;

	point_set(&player, game->bob.position.x, game->bob.position.y);
	if (theta == 0.0 || theta == 90.0 || theta == 180.0 || theta == 270.0)
		return (wall_execption(game, player, theta));
	horizontal = wall_horizontal(game, player, theta);
	vertical = wall_vertical(game, player, theta);
	return ((vertical < horizontal) ? vertical : horizontal);
}

/* EOF */
