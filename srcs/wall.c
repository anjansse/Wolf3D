#include "wolf.h"

static double	wall_horizontal(t_game *game, t_vector player, float theta)
{
	int			wall;
	double		x;
	double		y;
	t_vector	point;

	wall = 0;
	x = fabs(BLOCK_SIZE / tan(theta * M_PI / 180));
	y = BLOCK_SIZE;
	point_set(&point, player.x, player.y);
	point_update(&point, theta, x / 2.0, y / 2.0);
	while (SUCCESS == point_is_wall(game, point, &wall) && wall == 0)
		point_update(&point, theta, x + 0.0, y + 0.0);
	if (wall == 0)
		return (MAXFLOAT);
	return (sqrt(pow(point.x - player.x, 2) + pow(point.y - player.y, 2)));
}

static double	wall_vertical(t_game *game, t_vector player, float theta)
{
	int			wall;
	double		x;
	double		y;
	t_vector	point;

	wall = 0;
	x = BLOCK_SIZE;
	y = fabs(BLOCK_SIZE * tan(theta * M_PI / 180));
	point_set(&point, player.x, player.y);
	point_update(&point, theta, x / 2.0, y / 2.0);
	while (SUCCESS == point_is_wall(game, point, &wall) && wall == 0)
		point_update(&point, theta, x + 0.0, y + 0.0);
	if (wall == 0)
		return (MAXFLOAT);
	return (sqrt(pow(point.x - player.x, 2) + pow(point.y - player.y, 2)));
}

double			wall_distance(t_game *game, float theta)
{
	double		vertical;
	double		horizontal;
	t_vector	player;

	point_set(&player, game->bob.position.x, game->bob.position.y);
	horizontal = wall_horizontal(game, player, theta);
	vertical = wall_vertical(game, player, theta);
	return ((vertical < horizontal) ? vertical : horizontal);
}

/* EOF */
