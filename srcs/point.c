#include "wolf.h"

static int		point_is_wall(t_game *game, t_vector point, int *wall)
{
	int		x;
	int		y;

	// Need to Handle the case NaN
	x = (int)(point.x / BLOCK_SIZE);
	y = (int)(point.y / BLOCK_SIZE);
	// REMOVE JUST TO UNDERSTAND
	ft_printf("Point: [%d, %d]\n", x, y);
	// END
	if (0 <= x && x < game->x_max && 0 <= y && y < game->y_max)
	{
		if (game->map[y][x] != 0 && wall)
			*wall = 1;
		return (SUCCESS);
	}
	return (FAILURE);
}

static t_vector	checking_first_point(t_vector point, double theta, int horizontal)
{
	t_vector	first;

	if (horizontal)
	{
		if (theta == 0.0)
			first.y = point.y;
		else if (theta > 0.0)
			first.y = (floor(point.y / BLOCK_SIZE) * BLOCK_SIZE) - 1;
		else
			first.y = (floor(point.y / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		first.x = point.x + ((point.y - first.y) / tan(theta * (M_PI / 180)));
	}
	else
	{
		if (theta == 90.0 || theta == -90.0)
			first.x = point.x;
		else if (theta < 90.0 && theta > -90.0)
			first.x = floor((point.x / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		else
			first.x = floor((point.x / BLOCK_SIZE) * BLOCK_SIZE) - 1;
		first.y = point.y + ((point.x - first.x) * tan(theta * (M_PI / 180)));
	}
	return (first);
}

static double	checking_horizontal(t_game *game, double theta)
{
	int			wall;
	double		x;
	double		y;
	t_vector	point;

	wall = 0;
	point = checking_first_point(game->bob.position, theta, 1);
	if (FAILURE == point_is_wall(game, point, &wall))
		return (NAN);
	y = (theta <= 0) ? BLOCK_SIZE : -BLOCK_SIZE;
	x = BLOCK_SIZE / tan(theta * (M_PI / 180));
	while (SUCCESS == point_is_wall(game, point, &wall))
	{
		point.y += y;
		point.x += x;
	}
	return (fabs(game->bob.position.x - point.x) / cos(theta * (M_PI / 180)));
}

static double	checking_vertical(t_game *game, double theta)
{
	int			wall;
	double		x;
	double		y;
	t_vector	point;

	wall = 0;
	point = checking_first_point(game->bob.position, theta, 0);
	if (FAILURE == point_is_wall(game, point, &wall))
		return (NAN);
	x = (theta < 90.0 && theta > -90.0) ? BLOCK_SIZE : -BLOCK_SIZE;
	y = BLOCK_SIZE * tan(theta * (M_PI / 180));
	while (SUCCESS == point_is_wall(game, point, &wall))
	{
		point.x += x;
		if (theta == 0)
			point.y = point.y;
		else if (theta > 0)
			point.y -= y;
		else
			point.y += y;
	}
	return (fabs(game->bob.position.x - point.x) / cos(theta * (M_PI / 180)));
}

double			distance_wall(t_game *game, double theta)
{
	double	vertical;
	double	horizontal;

	theta = (theta > 180.0) ? theta - 360.0 : theta;
	horizontal = checking_horizontal(game, theta);
	// REMOVE JUST TO UNDERSTAND
	ft_printf("\n");
	// END
	vertical = checking_vertical(game, theta);
	// REMOVE JUST TO UNDERSTAND
	printf("%f | %f\n", horizontal, vertical);
	// END
	if (vertical == NAN)
		return (horizontal);
	else if (horizontal == NAN)
		return (vertical);
	return ((vertical < horizontal) ? vertical : horizontal);
}

/* EOF */
