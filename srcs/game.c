#include "../includes/wolf.h"

/*
** Loops until finds a wall on the ray.
*/ 

static t_uchar	wall_hit(t_game *game, t_point *map, t_vector *side, t_vector *delta)
{
	t_uchar 	hit;
	t_uchar		sideMap;

	hit = 0;
	while (hit == 0)
	{
		sideMap = (side->x < side->y) ? 0 : 1;
		if (side->x < side->y)
		{
			side->x += delta->x;
			map->x += game->step.x;
		}
		else
		{
			side->y += delta->y;
			map->y += game->step.y;
		}
		if (0 <= map->x && map->x < game->x_max && 0 <= map->y && map->y < game->y_max)
		{
			if (game->map[map->y][map->x] != 0)
				hit = 1;
		}
		else
			hit = 1;
	}
	return (sideMap);
}

/*
** DDA, find distances of walls if they exists and return it.
*/

static t_uchar	dda(t_game *game, t_vector *ray, t_point *map, double x)
{
	t_uchar		sideMap;
	double		camera;
	t_vector	side;
	t_vector	delta;

	camera = 2 * x / SCREEN_WIDTH - 1;
	point_set(map, PLAYER_POS.x, PLAYER_POS.y);
	vector_set(ray, PLAYER_DIR.x + PLAYER_PL.x * camera, PLAYER_DIR.y + PLAYER_PL.y * camera);
	vector_set(&delta, fabs(1 / ray->x), fabs(1 / ray->y));
	game->step.x = (ray->x < 0) ? -1 : 1;
	side.x = (ray->x < 0) ? (PLAYER_POS.x - map->x) * delta.x : (map->x + 1.0 - PLAYER_POS.x) * delta.x;
	game->step.y = (ray->y < 0) ? -1 : 1;
	side.y = (ray->y < 0) ? (PLAYER_POS.y - map->y) * delta.y : (map->y + 1.0 - PLAYER_POS.y) * delta.y;
	sideMap = wall_hit(game, map, &side, &delta);
	return (sideMap);
}

/*
** Gets distance for walls and display them.
** Does this for total width of opened window.
*/

static void		display_walls(t_game *game)
{
	double		wallDistance;
	t_vector	ray;
	t_point		map;
	t_uchar		sideMap;
	t_point		point;

	point_set(&point, 0, 0);
	while (point.x < SCREEN_WIDTH)
	{
		sideMap = dda(game, &ray, &map, point.x);
		if (sideMap == 0)
			wallDistance = (map.x - PLAYER_POS.x + (1 - game->step.x) / 2) / ray.x;
		else
			wallDistance = (map.y - PLAYER_POS.y + (1 - game->step.y) / 2) / ray.y;
		put_column(game, point, (int)(SCREEN_HEIGTH / wallDistance), 0x00FBFF);
		++point.x;
	}
}

/*
** Main function called in loop_hook. Used to print every element on the map
** (Walls, your imagination, that's it, ....)
*/

int				display_map(t_game *game)
{
	if (game->draw == 1)
	{
		put_background(game, PP_DIMENSION);
		display_walls(game);
		mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	}
	game->draw = 0;
	return (1);
}

/*
** Main Game function, initializes the window, prints background and walls
** contained into player's current fov, and get's user inputted keys.
*/

void			game_init(t_game game)
{
	int		pixels;
	int		size_line;
	int		endian;

	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH, "Wolf3D");
	game.image = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	game.pixels = (unsigned int *)mlx_get_data_addr(game.image, &pixels, &size_line, &endian);
	game.draw = 1;
	player_init(&(game.bob), 3, 3);
	mlx_hook(game.window, 2, 0, key_press, &game);
	// mlx_hook(game.window, 3, 0, key_release, &game);
	mlx_loop_hook(game.mlx, display_map, &game);
	mlx_loop(game.mlx);
}

/* EOF */
